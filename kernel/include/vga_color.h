#pragma once
#include <cstdint>

enum class Color : uint8_t {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15,
};

struct ColorCode {
    uint8_t code;

    constexpr ColorCode(Color fg, Color bg)
        : code((static_cast<uint8_t>(bg) >> 4) | static_cast<uint8_t>(fg)) {}

    constexpr operator uint8_t() const { return code; }
};