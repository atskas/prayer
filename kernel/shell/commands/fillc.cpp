#include "../../include/helper.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class FillChCommand : public Command {
public:
    const char* name() const override { return "fillc"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Fills the screen with a character.\n");
            vga_print("Usage: fillc <char>\n");
            return;
        }

        if (argc < 1) {
            vga_print("Usage: fillc <char>\n");
            return;
        }

        vga_clear();
        for (int row = 0; row < 25; row++) {
            for (int col = 0; col < 80; col++) {
                vga_printc(*argv[1]);
            }
        }
        vga_print("\n");
    }
};

REGISTER_COMMAND(FillChCommand);