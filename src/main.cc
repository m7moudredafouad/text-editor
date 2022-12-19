#include <gfx/gfx.h>
#include <gfx/lib_gfx.h>

void loop() {
    gfx::render_text("Mahmoud is here", 0.0f, 0.0f, "consola", 32);
    gfx::render_text("Hello", 0.0f, 20.0f, "arial");
}

int main() {
	gfx::create_window("Test", loop);

	exit(EXIT_SUCCESS);
}