#pragma once
#include <cstdint>

// CPU register state
struct regs_t {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void exc_init();

extern "C" void exception_common_handler(int vector, uint32_t error_code, regs_t* regs);

// Extern "C" on the stubs defined in the .asm file so the
// IDE doesn't freak out

extern "C" void isr0();
extern "C" void isr8();
extern "C" void isr13();
extern "C" void isr14();
