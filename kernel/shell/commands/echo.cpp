#include "../../include/shell/command.h"
#include "../../include/vga.h"

class EchoCommand : public Command {
public:
    const char* name() const override { return "echo"; }
    void execute(int argc, const char **argv) override {
        for (int i = 1; i < argc; i++) {
            vga_print(argv[i]);
            vga_print(" ");
        }
        vga_print("\n");
    }
};

REGISTER_COMMAND(EchoCommand);