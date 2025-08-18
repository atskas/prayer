#include "../../include/helper.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class RebootCommand : public Command {
public:
    const char* name() const override { return "reboot"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Reboots the computer.\n");
            vga_print("Usage: reboot\n");
            return;
        }

        asm volatile("cli"); // Disable interrupts
        outb(0x64, 0xFE); // Send reset command to the keyboard controller
        while (true); // Wait
    }
};

REGISTER_COMMAND(RebootCommand);