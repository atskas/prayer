#include "../include/shell/shell.h"
#include "../include/helper.h"
#include "../include/vga.h"
#include "../include/keyboard.h"

#define MAX_ARGS 20

void shell_loop() {
    char line[128];

    // Print the banner
    char input[] = "banner";
    handle_input(input);

    while (true) {
        vga_print("> "); // The prompt.
        read_line(line, sizeof(line));
        handle_input(line);
    }
}

int split_args(char* line, const char** argv) {
    int argc = 0;
    bool in_token = false;

    for (char* p = line; *p && argc < MAX_ARGS; p++) {
        if (*p == ' ' || *p == '\t' || *p == '\n') {
            *p = 0;       // null-terminate token
            in_token = false;
        } else if (!in_token) {
            argv[argc++] = p;
            in_token = true;
        }
    }

    return argc;
}

void handle_input(char* line) {
    const char* argv[20];
    int argc = split_args(line, argv);

    if (argc == 0) return;

    for (Command** cmd = &__start_commands; cmd < &__stop_commands; cmd++) {
        if (streq(argv[0], (*cmd)->name())) {
            (*cmd)->execute(argc, argv);
            return;
        }
    }

    vga_print("Unknown command: ");
    vga_print(line);
    vga_print("\n");
}