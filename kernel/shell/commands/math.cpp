#include "../../include/helper.h"
#include "../../include/shell/command.h"
#include "../../include/vga.h"

class MathCommand : public Command {
public:
    const char* name() const override { return "math"; }
    void execute(int argc, const char **argv) override {
        if (argc > 1 && streq(argv[1], "help")) {
            vga_print("Mathematical operations.\n");
            vga_print("Available operations: add, subtract, multiply, divide\n");
            vga_print("Usage: math <operation> <operand> <operand>..\n");
            return;
        }

        if (argc < 3) {
            vga_print("Usage: math <operation> <operand> <operand>...\n");
            return;
        }

        if (streq(argv[1], "add")) {
            int32_t result = stoi(argv[2]);
            for (int i = 3; i < argc; i++) {
                int32_t num = stoi(argv[i]);
                result += num;
            }

            char buf[12];
            itos(result, buf);
            vga_print("Result: ");
            vga_print(buf);
            vga_print("\n");
        } else if (streq(argv[1], "subtract")) {
            int32_t result = stoi(argv[2]);
            for (int i = 3; i < argc; i++) {
                int32_t num = stoi(argv[i]);
                result -= num;
            }

            char buf[12];
            itos(result, buf);
            vga_print("Result: ");
            vga_print(buf);
            vga_print("\n");
        } else if (streq(argv[1], "multiply")) {
            int32_t result = stoi(argv[2]);
            for (int i = 3; i < argc; i++) {
                int32_t num = stoi(argv[i]);
                result *= num;
            }

            char buf[12];
            itos(result, buf);
            vga_print("Result: ");
            vga_print(buf);
            vga_print("\n");
        } else if (streq(argv[1], "divide")) {
            int32_t result = stoi(argv[2]);
            for (int i = 3; i < argc; i++) {
                int32_t num = stoi(argv[i]);
                if (num == 0) {
                    vga_print("Error: division by 0\n");
                    return;
                }
                result /= num;
            }

            char buf[12];
            itos(result, buf);
            vga_print("Result: ");
            vga_print(buf);
            vga_print("\n");
        }
    }
};

REGISTER_COMMAND(MathCommand);