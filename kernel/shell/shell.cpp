#include "../include/shell/shell.h"
#include "../include/vga.h"
#include "../include/keyboard.h"

void shell_loop() {
    char line[128];

    while (true) {
        vga_print("> "); // The prompt.
        read_line(line, sizeof(line));
    }
}
