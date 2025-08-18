#include "../../include/helper.h"
#include "../../include/time.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class UptimeCommand : public Command {
public:
    const char* name() const override { return "uptime"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Prints the OS uptime in seconds / milliseconds.\n");
            vga_print("Usage: uptime\n");
            return;
        }

        char buf1[12], buf2[12];
        itos(s_since_boot(), buf1);
        itos(ms_since_boot(), buf2);
        vga_print(buf1);
        vga_print("s");
        vga_print(", ");
        vga_print(buf2);
        vga_print("ms");
        vga_print("\n");
    }
};

REGISTER_COMMAND(UptimeCommand);