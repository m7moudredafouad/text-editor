#pragma once

#include <gfx/gfx.h>
#include <gfx/Buffers.h>

struct BufferLayout {
    uint32_t length, type, normalize;
};

template <class vertex_t>
class Mesh {
protected:
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;

public:
    /***Constructors**********************************/
    Mesh(size_t max_size) :
        m_vao(std::shared_ptr<VertexArray>(new VertexArray)),
        m_vbo(std::shared_ptr<VertexBuffer>(new VertexBuffer(GL_ARRAY_BUFFER, sizeof(vertex_t) * max_size)))
    { }

    ~Mesh() {}

    /***Drawer****************************************/
    void layout(std::vector<BufferLayout> layouts) const {
        size_t stride = 0, offset = 0;
        for (auto& element : layouts) {
            stride += sizeofGlType(element.type) * element.length;
        }

        this->m_vao->bind();
        this->m_vbo->bind();
        for (size_t i = 0; i < layouts.size(); ++i) {

            auto& element = layouts[i];

            GLCall(glEnableVertexAttribArray(i));

            GLCall(glVertexAttribPointer(
                i, element.length, element.type, element.normalize, stride, reinterpret_cast<const void*>(offset)
            ));
            offset += element.length * sizeofGlType(element.type);

        }
    }

    virtual void Render(const std::vector<vertex_t> & obj) {
        m_vao->bind();
        m_vbo->bindData(obj, true);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * sizeof(obj)));
    }
};
