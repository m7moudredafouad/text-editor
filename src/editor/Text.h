#pragma once

#include <string>
#include <gfx/lib_gfx.h>
#include <utilities/error.h>
#include <utilities/data_types.h>
#include <editor/settings.h>

class Text {
    vec2 m_max_dims;
    std::string m_buffer;
public:
    Text(char * file_name) : m_max_dims{0.0f, 0.0f} {
        FILE *file;

        ASSERT((file = fopen(file_name, "r")) != nullptr, "File couldn't be opened");

        fseek(file, 0, SEEK_END);
        size_t len = ftell(file);
        ASSERT(len > 0, "File not successfully read");

        m_buffer = std::string(len+1, 0);

        fseek(file, 0, SEEK_SET);
        fread(&m_buffer[0], 1, len, file);

        ASSERT(m_buffer.length() == len + 1, "file wasn't fully read");
        ASSERT(fclose(file) == 0, "Couldn't close file");
    }
    ~Text() {}

    void Render() {
        m_max_dims = vec2(0.0f, 0.0f);

        float line_number = 0;
        vec2 pos = vec2(START_X, LINE_HEIGHT * FONT_SIZE * line_number + START_Y);

        for(const auto & the_char : m_buffer) {
            if(the_char != '\n') {
                pos.x = gfx::render_char(the_char, pos, gfx::sFont("consola", FONT_SIZE));
                continue;
            }
            
            line_number++;
            m_max_dims.x = std::max(m_max_dims.x, pos.x);
            pos = vec2(START_X, LINE_HEIGHT * FONT_SIZE * line_number + START_Y);
        }

        m_max_dims.y = pos.y;
    }

    vec2 get_dims() {return m_max_dims;}
};