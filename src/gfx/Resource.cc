#include "Resource.h"

std::vector<Character> chars(128);

std::unordered_map<ShaderEnum, Shader*> Resource::m_shaders = std::unordered_map<ShaderEnum, Shader*>();
ShaderEnum Resource::m_last_used_shader = ShaderEnum::NONE;

std::unordered_map<TextureEnum, Texture *> Resource::m_texture = std::unordered_map<TextureEnum, Texture *>();
TextureEnum Resource::m_last_used_texture = TextureEnum::NONE_TEXTUTE;

Character Resource::getChar(int idx) {return chars[idx];}


void Resource::startup() {
    // Create shaders
    m_shaders[ShaderEnum::BASIC] = new Shader("./shaders/basic");
    
    // Create textures
    FT_Library ft;
    ASSERT(FT_Init_FreeType(&ft) == 0, "ERROR::FREETYPE: Could not init FreeType Library");

    FT_Face face;
    ASSERT(FT_New_Face(ft, "./fonts/arial.ttf", 0, &face) == 0, "ERROR::FREETYPE: Failed to load font");

    FT_Set_Pixel_Sizes(face, 0, 48); 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
    m_texture[TextureEnum::BASIC_TEXTUTE] = new Texture();
    m_texture[TextureEnum::BASIC_TEXTUTE]->bind();
    sTexture tmp_texture_structre;

    // TODO: You need to move this from here
    for (uint8_t c = 0; c < 128; c++) {
        // load character glyph 
        ASSERT(FT_Load_Char(face, c, FT_LOAD_RENDER) == 0, "ERROR::FREETYTPE: Failed to load Glyph");
        
        // set texture options
        tmp_texture_structre.width = face->glyph->bitmap.width;
        tmp_texture_structre.height = face->glyph->bitmap.rows;
        tmp_texture_structre.format = GL_RED;
        tmp_texture_structre.data = face->glyph->bitmap.buffer;

        m_texture[TextureEnum::BASIC_TEXTUTE]->push(tmp_texture_structre);

        // now store character for later use
        chars[c] = {TextureEnum::BASIC_TEXTUTE,
                    tmp_texture_structre.width, tmp_texture_structre.height,
                    face->glyph->bitmap_left, face->glyph->bitmap_top,
                    face->glyph->advance.x};
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    m_texture[TextureEnum::BASIC_TEXTUTE]->bind();

}

void Resource::shutdown() {
    for (auto& shader : m_shaders) {
        delete shader.second;
    }

    for (auto& texture : m_texture) {
        delete texture.second;
    }
}

const Shader & Resource::getShader(ShaderEnum shaderName) {
    const auto & shader = m_shaders.find(shaderName);
    ASSERT(shader != m_shaders.end(), "Shader was not found");
    return *shader->second;
}

const Shader & Resource::useShader(ShaderEnum shaderName) {
    const auto& shader = getShader(shaderName);
    if(m_last_used_shader == shaderName) return shader;
    shader.bind();
    return shader;
}

const Texture & Resource::getTexture(TextureEnum textureName) {
    const auto & texture = m_texture.find(textureName);
    ASSERT(texture != m_texture.end(), "Texture was not found");
    return *texture->second;
}

const Texture & Resource::useTexture(TextureEnum textureName) {
    const auto& texture = getTexture(textureName);
    if(m_last_used_texture == textureName) return texture;
    texture.bind();
    return texture;
}

const Texture & Resource::useTexture(uint32_t textureName) {
    const auto & texture = m_texture.find(textureName);
    ASSERT(texture != m_texture.end(), "Texture was not found");
    if(m_last_used_texture == textureName) return texture;
    texture.bind();
    return texture;
}
