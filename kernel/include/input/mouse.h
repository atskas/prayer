#pragma once
#include <cstdint>

namespace mouse {
    extern int8_t mouse_cycle;
    extern int8_t mouse_packet[];
    extern int32_t cursor_x;
    extern int32_t cursor_y;

    // Updates cursor position and draws the mouse
    void handle_mouse_packet();
}
