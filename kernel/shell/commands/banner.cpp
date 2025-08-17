#include "../../include/shell/command.h"
#include "../../include/vga.h"

class BannerCommand : public Command {
public:
    const char* name() const override { return "banner"; }
    void execute(int argc, const char **argv) override {
        vga_print("PPPPP   RRRR    AAA  Y   Y  EEEEE  RRRR      +\n");
        vga_print("P   P   R   R  A   A  Y Y   E      R   R   +++++\n");
        vga_print("PPPPP   RRRR   AAAAA   Y    EEEE   RRRR      +\n");
        vga_print("P       R  R   A   A   Y    E      R  R      +\n");
        vga_print("P       R   R  A   A   Y    EEEEE  R   R     +\n");
        vga_print("----------------------------------------------\n");
    }
};

REGISTER_COMMAND(BannerCommand);