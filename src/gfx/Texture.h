#pragma once
#include "gfx.h"

enum TextureEnum {
    NONE_TEXTUTE,
    BASIC_TEXTUTE,
};

struct sTexture {
    uint32_t width, height, format;
    uint8_t * data;
};

class Texture {
private:
    uint32_t m_texture_id;
public:
    Texture() {
        GLCall(glGenTextures(1, &m_texture_id));
    }

    void push(sTexture texture) {
        this->bind();
        GLCall(glTexImage2D(
            GL_TEXTURE_2D, 0, texture.format, texture.width, texture.height,
            0, texture.format, GL_UNSIGNED_BYTE, texture.data));

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        this->unbind();
    }

    void bind() const {GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));}
    void unbind() const {GLCall(glBindTexture(GL_TEXTURE_2D, 0));}
    ~Texture() {GLCall(glDeleteTextures(1, &m_texture_id));}
};