#include "../kernel/include/inter.h"
#include "../kernel/include/vga.h"
#include "../kernel/include/io.h"
#include "include/keyboard.h"

// Implemented in `inter_asm.asm`
extern "C" void irq0_stub();
extern "C" void irq1_stub();
extern "C" void load_idt(IDTPtr*);

static IDTEntry idt[256]; // IDT Array
static IDTPtr idt_ptr;

void set_idt_entry(int vector, uint32_t handler, uint16_t selector, uint8_t type_attr) {
    idt[vector].offset_low = handler & 0xFFFF;
    idt[vector].selector = selector;
    idt[vector].zero = 0;
    idt[vector].type_attr = type_attr;
    idt[vector].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    // Timer IRQ0
    set_idt_entry(32, (uint32_t)irq0_stub, 0x08, 0x8E);

    // Keyboard IRQ1
    set_idt_entry(33, (uint32_t)irq1_stub, 0x08, 0x8E);

    load_idt(&idt_ptr);

    // Start PIC initialization
    outb(0x20, 0x11); // master
    outb(0xA0, 0x11); // slave

    // Set vector offsets
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    // Tell master PIC there is a slave at IRQ2
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // Set 8086/88 (MCS-80/85) mode
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    uint8_t mask = inb(0x21); // Read current mask
    mask &= ~0x01; // Clear bit to allow IRQ0
    mask &= ~0x02; // Clear bit to allow IRQ1
    outb(0x21, mask);

    asm volatile("sti"); // Enable global interrupts
}

// Keyboard input handler
extern "C" void irq1_handler() {
    uint8_t scancode = inb(0x60);

    bool released;
    const KeyCode key = scancode_to_key(scancode, &released);

    if (released) {
        if (key == KEY_LSHIFT || key == KEY_RSHIFT)
            shift_active = false;
        outb(0x20, 0x20);
        return;
    }
    if (key == KEY_LSHIFT || key == KEY_RSHIFT)
        shift_active = true;

    if (key == KEY_BACKSPACE && keyboard_len > 0) {
        keyboard_len--;
    } else {
        char c = keycode_to_char(key, shift_active);
        if (c && keyboard_len < 256) {
            keyboard_buffer[keyboard_len++] = c;
        }
    }


    outb(0x20, 0x20);
}

// Timer handler
extern "C" void irq0_handler() {
    outb(0x20, 0x20); // Tell PIC we're done
}

