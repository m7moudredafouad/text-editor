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

void window_clear() {
    Window::clear();
}

void move_text_window(vec2 pos) {
    Resource::useShader("text").setUniform("projection", glm::ortho(pos.x, pos.x + Window::width(), pos.y, pos.y + Window::height()));
}

std::queue<Keyboard> & get_keyboard() { return Window::keys; }
std::queue<Mouse> & get_mouse() { return Window::mouse; }
std::queue<WindowSize> & get_window_size() { return Window::window_size; }

vec2 get_mouse_pos() {return vec2({Window::mouse_x(), Window::mouse_y()});}

// Drawing Related functions
float render_char(const char the_char, vec2 pos, const sFont & font) {
    static CharMesh text_mesh(1);
    text_mesh.Render(the_char, pos.x, pos.y, pos.x, font.name, font.size, font.color);
    return pos.x;
}

void render_line(const std::string & text, vec2 pos, const sFont & font) {
    static CharMesh text_mesh(1000);
    int size = text.size(), next_idx = 0, next_size;

    while(size > 0) {
        next_size = std::min(size, 1000);
        text_mesh.Render(text.substr(next_idx, next_size), pos.x, pos.y, pos.x, font.name, font.size, font.color);
        size -= next_size;
        next_idx += next_size;
    }
}

void render_square(float x, float y, float w, float h, const float (&color)[4]) {
    static SquareMesh mesh(1);
    mesh.Render(x, y, w, h, color);
}


} // namespace gfx