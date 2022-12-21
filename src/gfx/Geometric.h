#pragma once

#include <gfx/gfx.h>
#include <gfx/Mesh.h>
#include <gfx/Resource.h>
#include <gfx/Window.h>

struct sSquareVertex {
    float pos[2];
    float color[4];
};

class square_vertex {
    sSquareVertex points[6];
public:
    square_vertex(float x, float y, float w, float h, const float (&color)[4]):
    points{
        {{x + w, y}, {color[0], color[1], color[2], color[3]}},
        {{x, y}, {color[0], color[1], color[2], color[3]}},
        {{x, y - h}, {color[0], color[1], color[2], color[3]}},            

        {{x + w, y - h}, {color[0], color[1], color[2], color[3]}},
        {{x + w, y}, {color[0], color[1], color[2], color[3]}},
        {{x, y - h}, {color[0], color[1], color[2], color[3]}},
    } {  }
};

class SquareMesh : public Mesh<square_vertex> {
public:
    SquareMesh(size_t max_size) : Mesh(max_size) {
        this->layout({
            {2, GL_FLOAT, true},
            {4, GL_FLOAT, true}
        });
    }

    void Render(const std::vector<square_vertex> & obj) override final {
        m_vao->bind();
        m_vbo->bindData(obj, true);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * sizeof(obj)));
    }

    void Render(float x, float y, float w, float h, const float (&color)[4]) {
        square_vertex tmp(x, Window::height() - y, w, h, color);
        Resource::useShader("basic");
        this->Render(std::vector<square_vertex> {tmp});
    }
};