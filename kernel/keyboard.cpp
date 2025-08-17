#include "include/keyboard.h"
#include "include/vga.h"

volatile char keyboard_buffer[KB_BUFFER_SIZE];
volatile uint32_t keyboard_len = 0;

char get_char_from_buffer() {
    while (keyboard_len == 0);
    char c = keyboard_buffer[0];
    for (uint32_t i = 1; i < keyboard_len; i++)
        keyboard_buffer[i-1] = keyboard_buffer[i];
    keyboard_len--;
    return c;
}

void read_line(char* buf, int maxLen) {
    int i = 0;
    while (true) {
        char c = get_char_from_buffer();
        if (c == '\n' || c == '\r') {
            buf[i] = 0;
            vga_print("\n");
            return;
        }
        if (c == '\b') {
            if (i > 0) { i--; vga_back(); }
        } else if (i < maxLen - 1) {
            buf[i++] = c;
            vga_printc(c);
        }
    }
}

bool shift_active = false;
static const char normal_map[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=','\b','\t',
    'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\',
    'z','x','c','v','b','n','m',',','.','/',0,
    '*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static const char shift_map[128] = {
    0, 27, '!','@','#','$','%','^','&','*','(',')','_','+','\b','\t',
    'Q','W','E','R','T','Y','U','I','O','P','{','}','\n',0,
    'A','S','D','F','G','H','J','K','L',':','"','~',0,'|',
    'Z','X','C','V','B','N','M','<','>','?',0,
    '*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

// Converts a KeyCode to a string
const char* keycode_to_string(KeyCode key, bool shift) {
    if (key >= 128) return "?";
    static char c[2] = {0,0};
    c[0] = shift ? shift_map[key] : normal_map[key];
    return c;
}

// Converts a KeyCode to a char
char keycode_to_char(KeyCode key, bool shift) {
    if (key >= 128) return '?';
    static char c = 0;
    c = shift ? shift_map[key] : normal_map[key];
    return c;
}

// Converts a scancode to a KeyCode
extern "C" KeyCode scancode_to_key(uint8_t scancode, bool* released) {
    *released = scancode & 0x80;
    uint8_t code = scancode & 0x7F;
    if (code < 128) return scancode_table[code];
    return KEY_UNKNOWN;
}
