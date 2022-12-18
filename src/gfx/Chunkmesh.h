#pragma once

#include <memory>
#include <vector>
#include <utils/error.h>

#include <models/Model.h>
#include <gfx/Resource.h>
#include <gfx/Buffers.h>
#include <gfx/Window.h>

struct BufferLayout {
    uint32_t length, type, normalize;
};

template <class vertex_t>
class Chunkmesh {
private:
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo, m_ibo;
    std::vector<vertex_t> m_vertex;

public:
    /***Constructors**********************************/
    Chunkmesh(size_t max_size);
    ~Chunkmesh() {}

    /***Drawer****************************************/
    void Render();
    void layout(std::vector<BufferLayout> layout) const;

    /***Getters***************************************/
    size_t size() const { return m_vertex.size(); }

    /***Setters***************************************/
    void push(vertex_t obj) {
        m_vertex.push_back(obj);
    }

    void Render(vertex_t obj) {
        m_vbo->bindData(std::vector<vertex_t> {obj}, true);
        
        m_vao->bind();
        m_vbo->bind();

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * m_vertex.size()));
    }
};

/***Constructors**********************************/
template <class vertex_t>
Chunkmesh<vertex_t>::Chunkmesh(size_t max_size) :
    m_vao(std::shared_ptr<VertexArray>(new VertexArray)),
    m_vbo(std::shared_ptr<VertexBuffer>(new VertexBuffer(GL_ARRAY_BUFFER, sizeof(vertex_t) * max_size))) {   }

/***Drawer****************************************/
template <class vertex_t>
void Chunkmesh<vertex_t>::Render() {
    if (m_vertex.size() == 0) return;

    m_vbo->bindData(m_vertex, true);

    m_vao->bind();
    m_vbo->bind();

    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6 * m_vertex.size()));
}

template <class vertex_t>
void Chunkmesh<vertex_t>::layout(std::vector<BufferLayout> layouts) const {
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