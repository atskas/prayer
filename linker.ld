ENTRY(_start)

MEMORY {
    RAM (rwx) : ORIGIN = 0x00100000, LENGTH = 16M
}

SECTIONS {
  . = 1M;

  .multiboot2 :
  {
    KEEP(*(.multiboot2))
  }

  /* reserve a 16 KB kernel stack */
  .kernel_stack_start = .;
  .stack (NOLOAD) :
  {
      . = . + 16K;
  } > RAM
  .kernel_stack_end = .;

  .text :
  {
    *(.text*)
  }

  .rodata : { *(.rodata*) }
  .data   : { *(.data*) }
  .bss    : {
    *(.bss*)
    *(COMMON)
  }
}
