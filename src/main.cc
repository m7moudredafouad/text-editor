#include <utilities/error.h>
#include <gfx/lib_gfx.h>
#include <editor/Document.h>
#include <editor/settings.h>

static std::shared_ptr<Document> test;

void loop() {
    test->Render();
}

int main(int argc, char **argv) {

    ASSERT(argc >= 2, "The program needs 1 argument to run");

    test = std::shared_ptr<Document> (new Document(argv[1]));

	gfx::create_window("Test", loop);
	exit(EXIT_SUCCESS);
}