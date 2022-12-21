#pragma once

#include <gfx/gfx.h>
#include <gfx/Mesh.h>
#include <gfx/Resource.h>
#include <gfx/Window.h>

struct sVertex {
    float pos[2];
    float texture_cord[2];
    float color[4];
};

class char_vertex {
    sVertex points[6];
public:
    char_vertex(float x, float y, float w, float h, const float (&color)[4]):
    points{
        {{x, y + h},      {0.0f, 0.0f}, {color[0], color[1], color[2], color[3]}},            
        {{x, y},          {0.0f, 1.0f}, {color[0], color[1], color[2], color[3]}},
        {{x + w, y},      {1.0f, 1.0f }, {color[0], color[1], color[2], color[3]}},

        {{x, y + h},      {0.0f, 0.0f }, {color[0], color[1], color[2], color[3]}},
        {{x + w, y},      {1.0f, 1.0f }, {color[0], color[1], color[2], color[3]}},
        {{x + w, y + h},  {1.0f, 0.0f }, {color[0], color[1], color[2], color[3]}}  
    } {  }
};

class CharMesh : public Mesh<char_vertex> {
public:
    CharMesh(size_t max_size) : Mesh(max_size) {
        this->layout({
            {2, GL_FLOAT, true},
            {2, GL_FLOAT, true},
            {4, GL_FLOAT, true}
        });
    }

    void Render(const std::vector<char_vertex> & obj) override final {
        m_vao->bind();
        m_vbo->bindData(obj, true);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * sizeof(obj)));
    }

    void Render(char ch, float x, float y, float & new_x, std::string font_name, int font_size, const float (&font_color)[4]) {
        float scale = (float)font_size / FONT_LOAD_SIZE;
        auto the_char = Resource::getChar(ch, font_name);

        new_x = x + (the_char.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)

        float xpos = x + the_char.bitmap_left * scale;
        float ypos = (Window::height() - y -font_size) - (the_char.height - the_char.bitmap_top) * scale;

        char_vertex tmp(xpos, ypos, the_char.width * scale, the_char.height * scale, font_color);

        Resource::useShader("text");
        Resource::useTexture(the_char.texture_id);
        this->Render(std::vector<char_vertex> {tmp});
    }
};