#include "../../include/shell/command.h"
#include "../../include/vga.h"

class HelpCommand : public Command {
public:
    const char* name() const override { return "help"; }
    void execute(int argc, const char **argv) override {
        vga_print("Available commands:\n");
        vga_print("echo - Mimics anything inputted right after the command name.\n");
        vga_print("color <fg> <bg> - Changes the foreground and background colors.\n");
        vga_print("banner - Displays the shell's banner.\n");
        vga_print("clear - Clears the screen.\n");
        vga_print("fillc <char> - Fills the screen with a specified character.\n");
        vga_print("help - This very screen.\n");
    }
};

REGISTER_COMMAND(HelpCommand);