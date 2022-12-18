#include <main.h>
#include <gfx/Character.h>

using testChar = Chunkmesh<Char>;
static std::shared_ptr<testChar> test_mesh;

Window * window = static_cast<Window *>(&Window::getInstance());

std::vector<std::vector<float>> ortho(float left, float right, float bottom, float top) {
    std::vector<std::vector<float>> Result(4, std::vector<float>(4, 1));
    Result[0][0] = static_cast<float>(2) / (right - left);
    Result[1][1] = static_cast<float>(2) / (top - bottom);
    Result[2][2] = - static_cast<float>(1);
    Result[3][0] = - (right + left) / (right - left);
    Result[3][1] = - (top + bottom) / (top - bottom);
    return Result;
}

void init() {
    srand (time(NULL));
    
    /***Renderer**************************************/
    Resource::startup();

    /***Camera****************************************/
    // Camera::startup(45);

    /***Game******************************************/
    test_mesh = std::shared_ptr<testChar>(new testChar(1));
    test_mesh->layout({
        {2, GL_FLOAT, true},
        {2, GL_FLOAT, true},
    });

    /***Projection************************************/
    Resource::useShader(ShaderEnum::BASIC).setUniform("projection", ortho(0, 800, 0, 600)).setUniform("text", 0);
}

void render() {
    int x = 100, y = 100;
    glActiveTexture(GL_TEXTURE0);
    for (uint8_t c = 65; c < 70; c++) {
        auto ch = Resource::getChar(c);

        float xpos = x + ch.bitmap_left;
        float ypos = y - (ch.height - ch.bitmap_top);

        float w = ch.width;
        float h = ch.height;
        // update VBO for each character
        Resource::useTexture(ch.TextureID);
        Char tmp(xpos, ypos, h, w);
        // test_mesh->push(tmp);
        test_mesh->Render(tmp);

        // render glyph texture over quad
        // glBindTexture(GL_TEXTURE_2D, ch.textureID);

        x += (ch.advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64)
    }
}

void destroy() {
    Resource::shutdown();
}

int main() {
	window->create();
	window->loop(init, render, destroy);

	return 0;
}


