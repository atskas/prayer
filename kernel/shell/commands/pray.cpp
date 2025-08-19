#include "../../include/helper.h"
#include "../../include/time.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class PrayCommand : public Command {
public:
    const char* name() const override { return "pray"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("A quick prayer for peace of mind.\n");
            vga_print("Usage: prayer\n");
            return;
        }

        wait_ms(500);
        vga_print("Our father, who art in heaven,\n");
        wait_ms(1000);
        vga_print("hallowed be thy name;\n");
        wait_ms(1000);
        vga_print("thy kingdom come; thy will be done,\n");
        wait_ms(1000);
        vga_print("on earth as it is in heaven.\n");
        wait_ms(1000);
        vga_print("Give us this day our daily bread, and forgive us our trespasses,\n");
        wait_ms(1000);
        vga_print("as we forgive those who trespass against us;\n");
        wait_ms(1000);
        vga_print("and lead us not into temptation, but deliver us from evil.\n");
        wait_ms(1000);
        vga_print("Amen.\n");
    }
};

REGISTER_COMMAND(PrayCommand);