#include <cstdint>

#include "../../include/graphics/graphics.h"
#include "../../include/graphics/ui/widget.h"

namespace gui {
    Widget widgets[MAX_WIDGETS];
    int widget_count = 0;

    Widget* create_widget(int x, int y, int w, int h) {
        if (widget_count >= MAX_WIDGETS) return 0;
        Widget* wdg = &widgets[widget_count++];

        wdg->x = x;
        wdg->y = y;
        wdg->w = w;
        wdg->h = h;
        wdg->visible = true;
        wdg->hovered = false;
        wdg->pressed = false;
        wdg->draw = 0;
        wdg->on_event = nullptr;
        wdg->on_update = nullptr;
        return wdg;
    }

    void draw() {
        for (int i = 0; i < widget_count; i++) {
            if (widgets[i].visible && widgets[i].draw) {
                widgets[i].draw(&widgets[i]);
            }
        }
    }

    void update(int mouse_x, int mouse_y, bool left_pressed) {
        for (int i = widget_count - 1; i >= 0; i--) {
            Widget* wdg = &widgets[i];
            if (!wdg->visible) continue;
            bool inside = mouse_x >= wdg->x && mouse_x < wdg->x + wdg->w &&
                    mouse_y >= wdg->y && mouse_y < wdg->y + wdg->h;

            if (inside) {
                wdg->hovered = true;
                if (wdg->on_event) wdg->on_event(wdg, HOVER);

                if (left_pressed && !wdg->pressed) {
                    wdg->pressed = true;
                    if (wdg->on_event)
                        wdg->on_event(wdg, CLICK);
                }

                if (!left_pressed && wdg->pressed) {
                    wdg->pressed = false;
                    if (wdg->on_event)
                        wdg->on_event(wdg, RELEASE);
                }
            } else {
                wdg->hovered = false;
                wdg->pressed = false;
            }

            if (wdg->on_update)
                wdg->on_update(wdg);
        }
    }
}
