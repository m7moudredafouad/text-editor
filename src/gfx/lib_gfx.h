#include <gfx/gfx.h>

namespace gfx {
void create_window(const char * name, void (*render)(void));
void render_text(const std::string & text, float x, float y, const std::string & font_name = "arial", int font_size = 48, const float (&font_color)[3] = {0xFF, 0xFF, 0xFF});
void render_char(const char the_char, float &x, float &y, const std::string & font_name, int font_size = 48, const float (&font_color)[3] = {0xFF, 0xFF, 0xFF});

}
