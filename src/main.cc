#include <utilities/error.h>
#include <gfx/lib_gfx.h>
#include <editor/Document.h>
#include <editor/settings.h>

static std::shared_ptr<Document> test;

void KeyboardEvents() {
    const auto & keys = gfx::get_keyboard();
    for(int i = GLFW_KEY_SPACE; i < GLFW_KEY_WORLD_2; i++) {
        if(keys.keys[i]) std::cout << char(i);
    }
}

void loop() {
    test->Render();
    KeyboardEvents();
}

int main(int argc, char **argv) {

    ASSERT(argc >= 2, "The program needs 1 argument to run");

    test = std::shared_ptr<Document> (new Document(argv[1]));

	gfx::create_window("Test", loop);
	exit(EXIT_SUCCESS);
}