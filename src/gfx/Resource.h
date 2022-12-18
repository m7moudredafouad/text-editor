#pragma once

#include <unordered_map>

#include "gfx.h"
#include "Buffers.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "Character.h"


enum ShaderEnum {
    NONE,
    BASIC,
};

/**
 * @brief Singleton Resource
 * 
 */
class Resource {
private:
    static std::unordered_map<ShaderEnum, Shader *> m_shaders;
    static ShaderEnum m_last_used_shader;
    static std::unordered_map<TextureEnum, Texture *> m_texture;
    static TextureEnum m_last_used_texture;

private: // PRIVATE FUNCTIONS
    Resource();
    Resource(const Resource&) = delete;
public:
    static void startup();
    static void shutdown();
    static const Shader & getShader(ShaderEnum shaderName);
    static const Shader & useShader(ShaderEnum shaderName);
    static const Texture & getTexture(TextureEnum textureName);
    static const Texture & useTexture(TextureEnum textureName);
    static const Texture & useTexture(uint32_t textureName);

    static Character getChar(int idx);
    ~Resource() {}

};  // class Renderer






