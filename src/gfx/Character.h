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

    void Render(char ch, float x, float y, float & new_x, std::string font_name, int font_size, const float (&font_color)[4]) {
        float scale = (float)font_size / FONT_LOAD_SIZE;
        auto the_char = Resource::getChar(ch, font_name);

        new_x = x + (the_char.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)

        float xpos = x + the_char.bitmap_left * scale;
        float ypos = (Window::height() - y -font_size) - (the_char.height - the_char.bitmap_top) * scale;

        char_vertex tmp(xpos, ypos, the_char.width * scale, the_char.height * scale, font_color);

        Resource::useTexture(the_char.texture_id);
        this->Render(std::vector<char_vertex> {tmp});
    }

    void Render(std::string text, float x, float y, float & new_x, std::string font_name, int font_size, const float (&font_color)[4]) {
        std::vector<std::vector<char_vertex>> char_data(128);
        std::vector<int> char_id(128);

        sCharDiscriptor chr_dscr;
        float xpos, ypos, scale = (float)font_size / FONT_LOAD_SIZE;

        for(const auto & ch : text) {
            chr_dscr = Resource::getChar(ch, font_name);

            xpos = x + chr_dscr.bitmap_left * scale;
            ypos = (Window::height() - y - font_size) - (chr_dscr.height - chr_dscr.bitmap_top) * scale;
            x += (chr_dscr.advance >> 6) * scale;

            char_data[int(ch)].push_back(char_vertex(xpos, ypos, chr_dscr.width * scale, chr_dscr.height * scale, font_color));
            char_id[int(ch)] = chr_dscr.texture_id;
        }

        for(int i = 0; i < 128; i++) {
            if(!char_data[i].size()) continue;
            Resource::useTexture(char_id[i]);
            this->Render(char_data[i]);
        }

        new_x = x;
    }

    void Render(const std::vector<char_vertex> & obj) override final {
        Resource::useShader("text");
        m_vao->bind();
        m_vbo->bindData(obj, true);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * obj.size()));
    }

};