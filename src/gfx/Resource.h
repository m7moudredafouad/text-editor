#pragma once

#include <gfx/gfx.h>
#include <gfx/Shader.h>
#include <gfx/Texture.h>

struct sCharDiscriptor {
    uint32_t texture_id, width, height;
    int32_t bitmap_left, bitmap_top, advance;
};

/**
 * @brief Singleton Resource
 * 
 */
class Resource {
private:
    static std::unordered_map<std::string, Shader *> m_shaders;
    static std::string m_last_used_shader;
    static std::unordered_map<uint32_t, Texture *> m_texture;
    static uint32_t m_last_used_texture;

    static std::unordered_map<std::string, std::vector<sCharDiscriptor>> m_fonts;
private: // PRIVATE FUNCTIONS
    Resource();
    Resource(const Resource&) = delete;
public:
    static void startup();
    static void shutdown();
    static const Shader & getShader(std::string shaderName);
    static const Shader & useShader(std::string shaderName);
    static const Texture & getTexture(uint32_t textureName);
    static const Texture & useTexture(uint32_t textureName);

    static void loadFont(std::string font_name, int pixel_size);
    static sCharDiscriptor getChar(char the_char, std::string font_name = "consola");
    ~Resource() {}

};  // class Renderer






