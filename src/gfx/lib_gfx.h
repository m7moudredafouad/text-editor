#pragma once
#include <gfx/gfx.h>

namespace gfx {

struct sFont {
    std::string name;
    int size;
    float color[3];

    sFont(const std::string & name = "consola", int size = 16, const float (&color)[3] = {0xFF, 0xFF, 0xFF}) :
        name(name), size(size), color{color[0], color[1], color[2]} { }
};

struct sPos {
    float x, y;
    sPos(float x, float y) : x(x), y(y) {}
};


void create_window(const char * name, void (*render)(void));
void render_char(const char the_char, float &x, float &y, const sFont & font);
void render_text(const std::string & text, sPos pos, const sFont & font);

}
