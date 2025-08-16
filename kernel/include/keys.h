#pragma once
#include <cstdint>

static const char* scancode_table[128] = {
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab",
    "Q", "W", "E", "R", "T", "Y", "U", "I",
    "O", "P", "[", "]", "Enter", "LCtrl", "A", "S",
    "D", "F", "G", "H", "J", "K", "L", ";",
    "'", "`", "LShift", "\\", "Z", "X", "C", "V",
    "B", "N", "M", ",", ".", "/", "RShift", "Keypad *",
    "LAlt", "Space", "CapsLock", "F1", "F2", "F3", "F4", "F5",
    "F6", "F7", "F8", "F9", "F10", "NumLock", "ScrollLock", "Keypad 7",
    "Keypad 8", "Keypad 9", "Keypad -", "Keypad 4", "Keypad 5", "Keypad 6", "Keypad +", "Keypad 1",
    "Keypad 2", "Keypad 3", "Keypad 0", "Keypad .", "?", "?", "?", "F11",
    "F12", "?", "?", "?", "?", "?", "?", "?",
    "?", "?", "?", "?", "?", "?", "?", "?"
};

// Converts the scancode hex value to a key
extern "C" const char* scancode_to_key(uint8_t scancode, bool* released);