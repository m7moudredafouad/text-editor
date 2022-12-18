#ifndef __BUFFERS_H_
#define __BUFFERS_H_

#include "gfx.h"
#include <vector>

/**
 * @brief BufferInterface
 * 
 */
class BufferInterface{
protected:
    uint32_t m_buffer_id;
public:
    BufferInterface() : m_buffer_id(0) {}
    virtual ~BufferInterface() {}
    virtual void bind() const  = 0;
    virtual void unbind() const = 0;
};


/**
 * @brief VertexArray (VAO)
 * 
 */
class VertexBuffer;
class VertexArray : public BufferInterface {
private:
    public:
    VertexArray() {
        glGenVertexArrays(1, &this->m_buffer_id);
        glBindVertexArray(this->m_buffer_id);
    }

    void bind() const override {GLCall(glBindVertexArray(m_buffer_id));}
    void unbind() const override {GLCall(glBindVertexArray(0));}
    ~VertexArray() {GLCall(glDeleteVertexArrays(1, &m_buffer_id));}
};


/**
 * @brief VertexBuffer (VBO)
 * 
 */
class VertexBuffer : public BufferInterface {
private:
    uint32_t m_buffer_type, m_data_lenght;

public:
    template <typename T>
    VertexBuffer(uint32_t buffer_type, const std::vector<T>& data) :
        m_buffer_type(buffer_type), m_data_lenght(data.size())
    {
        GLCall(glGenBuffers(1, &m_buffer_id));
        GLCall(glBindBuffer(m_buffer_type, m_buffer_id));
        GLCall(glBufferData(m_buffer_type, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW));
    }

    VertexBuffer(uint32_t buffer_type, size_t data_max_size) :
        m_buffer_type(buffer_type), m_data_lenght(0)
    {
        GLCall(glGenBuffers(1, &m_buffer_id));
        GLCall(glBindBuffer(m_buffer_type, m_buffer_id));
        GLCall(glBufferData(m_buffer_type, data_max_size, nullptr, GL_DYNAMIC_DRAW));
    }

    template <typename T>
    void bindData(const std::vector<T> &data, bool reset_offset = true) {
        this->bind();
        if (reset_offset) m_data_lenght = 0;
        GLCall(glBufferSubData(m_buffer_type, sizeof(T) * m_data_lenght, sizeof(T) * data.size(), &data[0]));
        m_data_lenght += data.size();
    }

    uint32_t length() const {return m_data_lenght;}

    void bind() const override {   GLCall(glBindBuffer(m_buffer_type, m_buffer_id));}
    void unbind() const override {GLCall(glBindBuffer(m_buffer_type, 0));}
    ~VertexBuffer() {GLCall(glDeleteBuffers(1, &m_buffer_id));}
};

#endif //   __BUFFERS_H_
