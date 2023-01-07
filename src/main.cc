#include <utilities/error.h>
#include <gfx/lib_gfx.h>
#include <editor/Document.h>
#include <editor/Commands.h>
#include <editor/settings.h>

static std::shared_ptr<Document> text_doc;


void KeyboardEvents() {
    auto & keys = gfx::get_keyboard();
    
    while (!keys.empty()) {
        auto e = keys.front();
        keys.pop();
        
        if(e.action == GLFW_RELEASE) continue;

        Command * cmd;

        if(e.key >= GLFW_KEY_SPACE && e.key <= GLFW_KEY_GRAVE_ACCENT) {
            cmd = new WriteCommand(text_doc, e);
        } else if(e.key == GLFW_KEY_ENTER) {
            cmd = new NewLineCommand(text_doc);
        }  else if(e.key == GLFW_KEY_BACKSPACE) {
            cmd = new RemoveCommand(text_doc);
        } else {
            cmd = new NothingCommand(text_doc);
        }

        cmd->execute();
        delete cmd;
    }
}

void MouseEvents() {
    vec2 mouse_pos = gfx::get_mouse_pos();
    auto & mouse = gfx::get_mouse();

    int mouse_queue_size = mouse.size();
    while (mouse_queue_size-- > 0){
        auto e = mouse.front();
        mouse.pop();

        e.dx = mouse_pos.x - e.x;
        e.dy = mouse_pos.y - e.y;
        e.x = mouse_pos.x;
        e.y = mouse_pos.y;
        
        if(mouse_queue_size && mouse.front().action == GLFW_RELEASE) {
            mouse.pop();
            mouse_queue_size--;
        } else {
            mouse.push(e);
        }

        if(e.key == GLFW_MOUSE_BUTTON_LEFT) {
            ClickCommand cmd(text_doc, e);
            cmd.execute();
        }
    }
}

void ResizeEvents() {
    auto & sizes = gfx::get_window_size();
    while (sizes.size() > 1) sizes.pop();

    if(sizes.size() == 1) {
        auto lastSize = sizes.front();
        sizes.pop();
        ResizeCommand cmd(text_doc, lastSize.width, lastSize.height);
        cmd.execute();
    }

}

void loop() {
    KeyboardEvents();
    MouseEvents();
    ResizeEvents();
    text_doc->Render();
}

int main(int argc, char **argv) {

    ASSERT(argc >= 2, "The program needs 1 argument to run");

    text_doc = std::shared_ptr<Document> (new Document(argv[1]));

	gfx::create_window(argv[1], loop);
	exit(EXIT_SUCCESS);
}