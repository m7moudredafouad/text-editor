#include <gfx/lib_gfx.h>
#include <gfx/Window.h>
#include <gfx/Character.h>
#include <gfx/Geometric.h>

namespace gfx {

// Window Related functions
static void init() {
    Resource::startup();
    Resource::loadFont("consola", FONT_LOAD_SIZE);
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

vec2 window_dims() {
    return vec2(Window::width(), Window::height());
}

void move_text_window(vec2 pos) {
    Resource::useShader("text").setUniform("projection", glm::ortho(pos.x, pos.x + Window::width(), pos.y, pos.y + Window::height()));
}

const Keyboard & get_keyboard() {
    return Window::keyboard;
}

const Mouse & get_mouse() {
    return Window::mouse;
}

// Drawing Related functions
float render_char(const char the_char, vec2 pos, const sFont & font) {
    static CharMesh text_mesh(1);
    text_mesh.Render(the_char, pos.x, pos.y, pos.x, font.name, font.size, font.color);
    return pos.x;
}

float render_text(const std::string & text, vec2 pos, const sFont & font) {
    for(const auto & ch : text) {
        pos.x = render_char(ch, pos, font);
    }

    return pos.x;
}

void render_square(float x, float y, float w, float h, const float (&color)[4]) {
    static SquareMesh mesh(1);
    mesh.Render(x, y, w, h, color);
}


} // namespace gfx