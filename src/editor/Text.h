#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <gfx/lib_gfx.h>
#include <utilities/error.h>
#include <utilities/data_types.h>
#include <editor/settings.h>
#include <editor/Cursor.h>

class Text {
    NormalCursor m_cursor;
    std::vector<std::string> m_lines;
    std::ifstream m_file;
    sDocumentFont m_font;

    vec2 m_max_dims,
         m_cursor_pos,   // Mouse Line number and position in the line
         m_window_dims, // Window Dimension
         m_cols_rows; // Window Dimension
private:
    void PositionToIndex(vec2 & pos) {
        // pos.x = (pos.x - START_X) / m_font.advance;
        // pos.y = (pos.y - START_Y) / (m_font.line_height * m_font.font_size);
        pos.x = (pos.x) / m_font.advance;
        pos.y = (pos.y) / (m_font.line_height * m_font.font_size);
    }

    void IndexToPosition(vec2 & pos) {
        // pos.x = m_font.advance * pos.x + START_X;
        // pos.y = m_font.font_size * m_font.line_height * pos.y + START_Y;
        // pos.y = START_Y + m_font.font_size * (pos.y * m_font.line_height + (m_font.line_height - 1) * 0.5);
        pos.x = m_font.advance * pos.x;
        pos.y = m_font.font_size * m_font.line_height * pos.y;
    }

public:
    vec2 get_dims() {return {m_max_dims.x * m_font.advance, m_font.line_height * m_font.font_size * m_lines.size()};}

    Text(char * file_name) : m_font{0, 0} {
        m_file.open(file_name);
        std::string line;
         if (m_file.is_open()) {
            while (getline(m_file, line)) {
                m_lines.push_back(line);
                m_max_dims.x = std::max(size_t(m_max_dims.x), line.size());
            }
            
            m_file.close();
        }
    }
    ~Text() {}

    void Render(vec2 start_pos) {
        // m_cursor_pos -= start_pos;
        PositionToIndex(start_pos);
        start_pos.x = std::floor(start_pos.x);
        start_pos.y = std::floor(start_pos.y);
        // PositionToIndex(m_cursor_pos);
        for(int i = start_pos.y; i < std::min(size_t(start_pos.y + m_cols_rows.y+1), m_lines.size()); i++) {
            vec2 pos = vec2(0, i);
            IndexToPosition(pos);

            for(const auto & the_char : m_lines[i]) {
                pos.x = gfx::render_char(the_char, pos, gfx::sFont("consola", m_font.font_size));
            }

            if(i == m_cursor_pos.y){ 
                m_cursor_pos.x = std::min(float(m_lines[i].length()), m_cursor_pos.x);
            }

        }

        std::cout << "Line: " << start_pos.y << " ==== > " << start_pos.y + m_cols_rows.y << std::endl;

        // IndexToPosition(m_cursor_pos);
        // IndexToPosition(start_pos);
        // m_cursor_pos += start_pos;
        // m_cursor.Render({m_cursor_pos.x + START_X, m_cursor_pos.y + START_Y});
    }

    void onClick(vec2 pos) {
        m_cursor_pos = pos;
    }

    void onResize(int width, int height) {
        m_window_dims = {width, height};
        m_cols_rows.x = std::floor(width / m_font.advance);
        m_cols_rows.y = std::floor(height / (m_font.line_height * m_font.font_size));
    }

    void onFontUpdate(const sDocumentFont & font) {m_font = font;}

};