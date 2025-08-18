#include "../../include/helper.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class ShutdownCommand : public Command {
public:
    const char* name() const override { return "shutdown"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Shuts down the computer.\n");
            vga_print("Usage: shutdown\n");
            return;
        }

        asm volatile("cli; hlt"); // Disable interrupts and halt the CPU
    }
};

REGISTER_COMMAND(ShutdownCommand);