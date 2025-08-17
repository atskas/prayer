#include "../../include/helper.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class TextColorCommand : public Command {
public:
    const char* name() const override { return "color"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Available colors:\n0(BLACK)\n1(BLUE)\n2(GREEN)\n3(CYAN)\n4(RED)\n5(MAGENTA)\n6(BROWN)\n7(LIGHT_GRAY)\n8(DARK_GRAY)\n9(LIGHT_BLUE)\n10(LIGHT_GREEN)\n11(LIGHT_CYAN)\n12(LIGHT_RED)\n13(LIGHT_MAGENTA)\n14(YELLOW)\n15(WHITE)\n");
            vga_print("Run the `clear` command right after changing colors for full appliance.\n");
            vga_print("Usage: color <fg> <bg>\n");
            return;
        }

        if (argc < 3) {
            vga_print("Usage: color <fg> <bg>\n");
            return;
        }

        int fg = stoi(argv[1]);
        int bg = stoi(argv[2]);
        vga_set_color((Color)fg, (Color)bg);
    }
};

REGISTER_COMMAND(TextColorCommand);