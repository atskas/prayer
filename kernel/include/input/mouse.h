#pragma once
#include <cstdint>
#include "../graphics/graphics.h"

enum MouseButton : uint8_t {
    LEFT = 0,
    RIGHT,
    MIDDLE,
    MBUTTON_COUNT
};

namespace mouse {
    extern int8_t mouse_cycle;
    extern int8_t mouse_packet[];
    extern volatile bool mouse_buttons[MBUTTON_COUNT];
    extern int32_t cursor_x, cursor_y;

    constexpr int cursor_w = 8;
    constexpr int cursor_h = 8;
    extern graphics::PixelColor cursor_bitmap[cursor_h][cursor_w];

    // Updates cursor position and draws the mouse
    void handle_mouse_packet();

    bool mouse_button_pressed(MouseButton button);
    void get_mouse_position(int32_t* x, int32_t* y);
    void draw_cursor(int x_pos, int y_pos);
}
