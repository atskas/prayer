#include "../kernel/include/inter.h"
#include "../kernel/include/vga.h"
#include "../kernel/include/helper.h"
#include "include/input/keyboard.h"
#include "include/time.h"
#include "include/graphics/graphics.h"
#include "include/input/mouse.h"

// Implemented in `inter_asm.asm`
extern "C" void irq0_stub();
extern "C" void irq1_stub();
extern "C" void irq12_stub();
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

// This entire function needs cleanup, TODO
void idt_init() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    // Timer IRQ0
    set_idt_entry(32, (uint32_t)irq0_stub, 0x08, 0x8E);

    // Keyboard IRQ1
    set_idt_entry(33, (uint32_t)irq1_stub, 0x08, 0x8E);

    // Mouse IRQ12
    set_idt_entry(44, (uint32_t)irq12_stub, 0x08, 0x8E);

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

    uint8_t mask = inb(0x21); // master PIC mask
    mask &= ~0x01; // unmask IRQ0
    mask &= ~0x02; // unmask IRQ1
    mask &= ~0x04; // unmask irq2 (lets slave PIC through)
    outb(0x21, mask);

    mask = inb(0xA1); // slave PIC mask
    mask &= ~(1 << 4); // unmask IRQ12
    outb(0xA1, mask);

    outb(0x64, 0xA8); // enable mouse port
    outb(0x64, 0x20); // tell controller to read command byte
    uint8_t status = inb(0x60);

    status |= 0x03; // bit 0 = keyboard IRQ, bit 1 = mouse IRQ
    outb(0x64, 0x60); // tell controller we’re writing command byte
    outb(0x60, status);

    // Reset the mouse
    outb(0x64, 0xD4);
    outb(0x60, 0xFF);
    while (inb(0x60) != 0xFA) {} // ACK
    while (inb(0x60) != 0xAA) {} // Self-test pass

    // Enable data reporting
    outb(0x64, 0xD4);
    outb(0x60, 0xF4);
    while (inb(0x60) != 0xFA) {} // ACK

    asm volatile("sti"); // Enable global interrupts
}

// Keyboard input handler
extern "C" void irq1_handler() {
    const uint8_t scancode = inb(0x60);

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

    if (key == KEY_BACKSPACE) {
        if (keyboard_len > 0) {
            keyboard_len--;
            keyboard_buffer[keyboard_len] = 0;
            outb(0x20, 0x20);
            return;
        }
    }

    char c = keycode_to_char(key, shift_active);
    if (c && keyboard_len < KB_BUFFER_SIZE) {
        keyboard_buffer[keyboard_len++] = c;
    }


    outb(0x20, 0x20); // Tell PIC we're done
}

// Timer handler
extern "C" void irq0_handler() {
    pit_tick();
    outb(0x20, 0x20); // Tell PIC we're done
}

// Mouse handler
extern "C" void irq12_handler() {
    mouse::handle_mouse_packet();

    outb(0xA0, 0x20); // Tell slave PIC we're done
    outb(0x20, 0x20); // Tell master PIC we're done
}

