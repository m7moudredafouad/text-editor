#include <utilities/error.h>
#include <gfx/lib_gfx.h>
#include <editor/Document.h>
#include <editor/Commands.h>
#include <editor/settings.h>

static std::shared_ptr<Document> test;

void KeyboardEvents() {
    auto & keys = gfx::get_keyboard();
    
    while (!keys.empty()) {
        auto e = keys.front();
        keys.pop();
        
        if(e.action == GLFW_RELEASE) continue;

        if(e.key >= GLFW_KEY_SPACE && e.key <= GLFW_KEY_GRAVE_ACCENT) {
            WriteCommand cmd(test, e);
            cmd.execute();
        }
    }
}

void MouseEvents() {
    auto & mouse = gfx::get_mouse();
    
    while (!mouse.empty()) {
        auto e = mouse.front();
        mouse.pop();
        
        if(e.action == GLFW_RELEASE) continue;

        if(e.key == GLFW_MOUSE_BUTTON_LEFT) {
            ClickCommand cmd(test);
            cmd.execute();
            std::cout << e.x << ", " << e.y;
        }
    }
    
}

void loop() {
    KeyboardEvents();
    MouseEvents();
    test->Render();
}

int main(int argc, char **argv) {

    ASSERT(argc >= 2, "The program needs 1 argument to run");

    test = std::shared_ptr<Document> (new Document(argv[1]));

	gfx::create_window("Test", loop);
	exit(EXIT_SUCCESS);
}