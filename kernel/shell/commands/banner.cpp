#include "../../include/helper.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class BannerCommand : public Command {
public:
    const char* name() const override { return "banner"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Displays the shell's banner.\n");
            vga_print("Usage: banner\n");
            return;
        }

        vga_print("######  #######  ##### ##   ## ##### ######      *\n");
        vga_print("##   ## ##   ## ##  ## ##   ## ##    ##   ##   *****\n");
        vga_print("######  ######  ######  ## ##  ##### ######      *\n");
        vga_print("##      ##  ##  ##  ##   ##    ##    ##  ##      *\n");
        vga_print("##      ##   ## ##  ##   ##    ##### ##   ##     *\n");
        vga_print("------------------------------------------------------\n");
        vga_print("|               run `help` for info                  |\n");
        vga_print("------------------------------------------------------\n");
    }
};

REGISTER_COMMAND(BannerCommand);