#pragma once
#include <gfx/gfx.h>
#include <gfx/Window.h>
#include <utilities/data_types.h>

namespace gfx {

struct sFont {
    std::string name;
    int size;
    float color[4];

    sFont(const std::string & name, int size, const float (&color)[4] = {0xC8, 0xC8, 0xC8, 0xFF}) :
        name(name), size(size), color{color[0], color[1], color[2]} { }
};

// Window Related functions
void create_window(const char * name, void (*render)(void));
vec2 window_dims();
void move_text_window(vec2 pos);

std::queue<Keyboard> & get_keyboard();
std::queue<Mouse> & get_mouse();
std::queue<WindowSize> & get_window_size();
vec2 get_mouse_pos();

// Drawing Related functions
float render_char(const char the_char, vec2 pos, const sFont & font);
float render_text(const std::string & text, vec2 pos, const sFont & font);
void render_square(float x, float y, float w, float h, const float (&color)[4]);




} // namespace gfx
