#pragma once

#include <string>
#include <gfx/lib_gfx.h>
#include <utilities/error.h>
#include <utilities/data_types.h>
#include <editor/settings.h>
#include <editor/Cursor.h>

class Text {
    NormalCursor m_cursor;
    std::string m_buffer;

    vec2 m_max_dims,
        m_cursor_pos;   // Mouse Line number and position in the line
public:
    Text(char * file_name) : m_max_dims{0.0f, 0.0f}, m_cursor_pos(0, 0) {
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
        static bool render_cursor = false;
        static int cursor_number_frame = CURSOR_RENDER_FRAME;

        m_max_dims = vec2(0.0f, 0.0f);

        float line_number = 0;
        vec2 pos = vec2(START_X, LINE_HEIGHT * FONT_SIZE * line_number + START_Y);

        for(const auto & the_char : m_buffer) {
            if(the_char != '\n') {
                pos.x = gfx::render_char(the_char, pos, gfx::sFont("consola", FONT_SIZE));
                
                continue;
            }

            int last_char_number = std::floor((pos.x - START_X) / 9);
            
            if(line_number == m_cursor_pos.y && last_char_number < m_cursor_pos.x) {
                m_cursor_pos.x = last_char_number;
            }

            line_number++;
            m_max_dims.x = std::max(m_max_dims.x, pos.x);
            pos = vec2(START_X, LINE_HEIGHT * FONT_SIZE * line_number + START_Y);


        }

        pos = vec2(START_X, LINE_HEIGHT * FONT_SIZE * (line_number+1) + START_Y);
        m_max_dims.y = pos.y;

        if(--cursor_number_frame < 0) {
            cursor_number_frame = CURSOR_RENDER_FRAME;
            render_cursor = !render_cursor;
        }
        if(render_cursor) this->m_cursor.Render(m_cursor_pos);
    }

    void onClick(vec2 pos) {
        // Calculate Mouse Position
        m_cursor_pos.x = std::floor(pos.x / 9);
        m_cursor_pos.y = std::floor(pos.y / (LINE_HEIGHT * FONT_SIZE));
        std::cout << "Cursor Coord: " << m_cursor_pos.x << ", " << m_cursor_pos.y+1 << std::endl;

        // Calculate Mouse Coordinates
        // pos.y = m_cursor_pos.y * LINE_HEIGHT * FONT_SIZE + START_Y + (LINE_HEIGHT - 1) * FONT_SIZE / 2;
    }

    vec2 get_dims() {return m_max_dims;}
};