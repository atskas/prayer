#include "../include/input/mouse.h"
#include "../include/helper.h"
#include "../include/graphics/graphics.h"

namespace mouse {
    int8_t mouse_cycle = 0;
    int8_t mouse_packet[3];
    volatile bool mouse_buttons[MBUTTON_COUNT] = {false};
    int32_t cursor_x = 100;
    int32_t cursor_y = 100;

    bool mouse_button_pressed(MouseButton button) {
        return mouse_buttons[button];
    }

    void draw_cursor() {
        // draw cursor
        graphics::putp(cursor_x, cursor_y, graphics::WHITE);
    }

    void handle_mouse_packet() {
        uint8_t data = inb(0x60); // read from PS/2 data port

        switch (mouse_cycle) {
            case 0:
                if (!(data & 0x08)) return; // ensure sync on bit 3
                mouse_packet[0] = data;
                mouse_cycle++;
                break;
            case 1:
                mouse_packet[1] = data;
                mouse_cycle++;
                break;
            case 2:
                mouse_packet[2] = data;
                mouse_cycle = 0;

                int8_t dx = mouse_packet[1];
                int8_t dy = mouse_packet[2];

                // track positions
                cursor_x += dx;
                cursor_y -= dy;

                mouse_buttons[LEFT] = mouse_packet[0] & 0x1;
                mouse_buttons[RIGHT] = mouse_packet[0] & 0x2;
                mouse_buttons[MIDDLE] = mouse_packet[0] & 0x4;

                // clamp to screen
                if (cursor_x < 0) cursor_x = 0;
                if (cursor_x >= (int32_t)graphics::width) cursor_x = graphics::width - 1;
                if (cursor_y < 0) cursor_y = 0;
                if(cursor_y >= (int32_t)graphics::height) cursor_y = graphics::height - 1;

                break;
        }
    }
}
