#pragma once
#include "widget.h"

namespace gui {
    extern Widget widgets[MAX_WIDGETS];
    extern int widget_count;

    Widget* create_widget(int x, int y, int w, int h);

    void draw();

    void update(int mouse_x, int mouse_y, bool left_pressed);
}
