#pragma once

#include <gfx/gfx.h>
#include <gfx/Mesh.h>
#include <gfx/Resource.h>

struct sVertex {
    float pos[2];
    float texture_cord[2];
};

class char_vertex {
    sVertex points[6];
public:
    char_vertex(float x, float y, float w, float h):
    points{
        {{x, y + h},      {0.0f, 0.0f}},            
        {{x, y},          {0.0f, 1.0f}},
        {{x + w, y},      {1.0f, 1.0f }},

        {{x, y + h},      {0.0f, 0.0f }},
        {{x + w, y},      {1.0f, 1.0f }},
        {{x + w, y + h},  {1.0f, 0.0f }}  
    } {  }
};

class CharMesh : public Mesh<char_vertex> {
public:
    CharMesh(size_t max_size) : Mesh(max_size) {
        this->layout({
            {2, GL_FLOAT, true},
            {2, GL_FLOAT, true}
        });
    }

    void Render(const std::vector<char_vertex> & obj) override final {
        m_vao->bind();
        m_vbo->bindData(obj, true);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * sizeof(obj)));
    }

    void Render(char ch, std::string font_name, float x, float y, float & new_x) {
        auto the_char = Resource::getChar(ch, font_name);

        new_x = x + (the_char.advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64)

        float xpos = x + the_char.bitmap_left;
        float ypos = y - (the_char.height - the_char.bitmap_top);

        char_vertex tmp(xpos, ypos, the_char.width, the_char.height);

        Resource::useTexture(the_char.texture_id);
        this->Render(std::vector<char_vertex> {tmp});
    }
};
