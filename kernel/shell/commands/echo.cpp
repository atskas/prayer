#include "../../include/helper.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class EchoCommand : public Command {
public:
    const char* name() const override { return "echo"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Mimics anything right after the command name.\n");
            vga_print("Usage: echo <args...>\n");
            return;
        }

        if (argc < 1) {
            vga_print("Usage: echo <args...>\n");
        }

        for (int i = 1; i < argc; i++) {
            vga_print(argv[i]);
            vga_print(" ");
        }
        vga_print("\n");
    }
};

REGISTER_COMMAND(EchoCommand);