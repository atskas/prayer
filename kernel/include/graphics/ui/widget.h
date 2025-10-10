#pragma once

#define MAX_WIDGETS 64

struct Widget {
    int x, y, w, h;
    bool visible;
    bool hovered, pressed;
    uint32_t color;
    void (*draw)(Widget* self);
    void (*on_click)(Widget* self);
    void (*on_release)(Widget* self);
};

extern Widget widgets[MAX_WIDGETS];
extern int widget_count;