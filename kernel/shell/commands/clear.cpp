#include "../../include/helper.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class ClearCommand : public Command {
public:
    const char* name() const override { return "clear"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Clears the entire screen.\n");
            vga_print("Usage: clear\n");
            return;
        }

        vga_clear();
    }
};

REGISTER_COMMAND(ClearCommand);