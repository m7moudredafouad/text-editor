#include <gfx/lib_gfx.h>
#include <gfx/Window.h>
#include <gfx/Character.h>

namespace gfx {

static void init() {
    Resource::startup();
    GLCall(glActiveTexture(GL_TEXTURE0));
}

static void destroy() {
    Resource::shutdown();
}

void create_window(const char * name, void (*render)(void)) {
    static auto window = &Window::getInstance();

    window->create(name);
	window->loop(init, render, destroy);
}

void render_char(const char the_char, float &x, float &y, const sFont & font) {
    static CharMesh text_mesh(1);
    text_mesh.Render(the_char, x, y, x, font.name, font.size, font.color);
}

void render_text(const std::string & text, sPos pos, const sFont & font) {
    for(const auto & ch : text) {
        render_char(ch, pos.x, pos.y, font);
    }
}


} // namespace gfx