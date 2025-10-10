#pragma once
#include "widget.h"

namespace gui {
    extern Widget widgets[MAX_WIDGETS];
    extern int widget_count;

    Widget* create_widget(int x, int y, int w, int h);

    void draw_widgets();

    void draw_test_button(Widget* wdg);

    void handle_mouse_event(int mouse_x, int mouse_y, bool left_pressed);
}
