#pragma once

#define MAX_WIDGETS 64

enum WidgetEvent {
    CLICK,
    RELEASE,
    HOVER,
};

struct Widget {
    int x, y, w, h;
    bool visible;
    bool hovered, pressed;
    int z_index;
    graphics::PixelColor color;
    void (*draw)(Widget* self);
    void (*on_event)(Widget* self, WidgetEvent event);
    void (*on_update)(Widget* self);
};

extern Widget widgets[MAX_WIDGETS];
extern int widget_count;