#include "Resource.h"

std::unordered_map<std::string, Shader*> Resource::m_shaders = std::unordered_map<std::string, Shader*>();
std::string Resource::m_last_used_shader = "";

std::unordered_map<uint32_t, Texture *> Resource::m_texture = std::unordered_map<uint32_t, Texture *>();
uint32_t Resource::m_last_used_texture = 0;

std::unordered_map<std::string, std::vector<sCharDiscriptor>> Resource::m_fonts = std::unordered_map<std::string, std::vector<sCharDiscriptor>>();

void Resource::startup() {
    // Create shaders
    m_shaders["text"] = new Shader("./shaders/text");
    
    Resource::loadFont("arial");
}

void Resource::shutdown() {
    for (auto& shader : m_shaders) {
        delete shader.second;
    }

    for (auto& texture : m_texture) {
        delete texture.second;
    }
}

void Resource::loadFont(std::string font_name) {
    
    if(m_fonts.count(font_name) != 0) return;

    FT_Library ft;
    ASSERT(FT_Init_FreeType(&ft) == 0, "ERROR::FREETYPE: Could not init FreeType Library");

    FT_Face face;
    std::string font_path = "./fonts/" + font_name + ".ttf";
    ASSERT(FT_New_Face(ft, &font_path[0], 0, &face) == 0, "ERROR::FREETYPE: Failed to load font");

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
    sTexture tmp_texture_structre;

    for (uint8_t c = 0; c < 128; c++) {
        // load character glyph 
        ASSERT(FT_Load_Char(face, c, FT_LOAD_RENDER) == 0, "ERROR::FREETYTPE: Failed to load Glyph");
        
        // set texture options
        tmp_texture_structre.width = face->glyph->bitmap.width;
        tmp_texture_structre.height = face->glyph->bitmap.rows;
        tmp_texture_structre.format = GL_RED;
        tmp_texture_structre.data = face->glyph->bitmap.buffer;

        auto texture = new Texture(tmp_texture_structre);

        // now store character for later use
        m_fonts[font_name].push_back({
                        texture->get_id(),
                        tmp_texture_structre.width,
                        tmp_texture_structre.height,
                        face->glyph->bitmap_left,
                        face->glyph->bitmap_top,
                        face->glyph->advance.x
                    });
        m_texture[texture->get_id()] = std::move(texture);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

const Shader & Resource::getShader(std::string shaderName) {
    const auto & shader = m_shaders.find(shaderName);
    ASSERT(shader != m_shaders.end(), "Shader was not found");
    return *shader->second;
}

const Shader & Resource::useShader(std::string shaderName) {
    const auto& shader = getShader(shaderName);
    if(m_last_used_shader == shaderName) return shader;
    shader.bind();
    return shader;
}

const Texture & Resource::getTexture(uint32_t textureName) {
    const auto & texture = m_texture.find(textureName);
    ASSERT(texture != m_texture.end(), "Texture was not found");
    return *texture->second;
}

const Texture & Resource::useTexture(uint32_t textureName) {
    const auto& texture = getTexture(textureName);
    if(m_last_used_texture == textureName) return texture;
    texture.bind();
    return texture;
}

sCharDiscriptor Resource::getChar(char the_char, std::string font_name) {
    const auto & font = m_fonts.find(font_name);
    ASSERT(font != m_fonts.end(), "Font was not found");
    return font->second[the_char];
}
