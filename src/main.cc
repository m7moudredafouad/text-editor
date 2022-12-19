#include <main.h>

static std::shared_ptr<CharMesh> text;

Window * window = static_cast<Window *>(&Window::getInstance());

void init() {
    Resource::startup();
    text = std::shared_ptr<CharMesh>(new CharMesh(1));
}

void render() {
    float x = 100, y = 100;
    glActiveTexture(GL_TEXTURE0);
    for (uint8_t c = 65; c < 70; c++) {
        text->Render(c, "arial", x, y, x);
    }
}

void destroy() {
    Resource::shutdown();
}

int main() {
	window->create();
	window->loop(init, render, destroy);

	exit(EXIT_SUCCESS);
}


