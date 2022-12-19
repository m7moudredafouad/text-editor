#pragma once

#include <gfx/gfx.h>

struct sTexture {
    uint32_t width, height, format;
    uint8_t * data;
};

class Texture {
private:
    uint32_t m_texture_id;
public:
    Texture(sTexture texture) {
        GLCall(glGenTextures(1, &m_texture_id));
        this->bind();

        GLCall(glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height,
            0, texture.format, GL_UNSIGNED_BYTE, texture.data));

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        this->unbind();
    }

    uint32_t get_id() {return m_texture_id;}

    void bind() const {GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));}
    void unbind() const {GLCall(glBindTexture(GL_TEXTURE_2D, 0));}
    ~Texture() {GLCall(glDeleteTextures(1, &m_texture_id));}
};