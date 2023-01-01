#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <gfx/lib_gfx.h>
#include <utilities/error.h>
#include <utilities/data_types.h>
#include <editor/settings.h>

class Text {
    std::vector<std::string> m_lines;
    std::ifstream m_file;
    sDocumentFont m_font;

    vec2 m_text_width_height,
         m_window_dims, // Window Dimension
         m_cols_rows; // Window Dimension
public:
    vec2 dimension_to_idx(const vec2 & pos) {
        return vec2 {
            pos.x / m_font.advance,
            pos.y / (m_font.line_height * m_font.font_size)
        };
    }

    vec2 idx_to_dimension(const vec2 & pos) {
        return vec2 {
            m_font.advance * pos.x,
            m_font.font_size * m_font.line_height * pos.y
        };
    }

    vec2 get_cursor_idx(const vec2 & pos) {
        int line_number = std::floor(pos.y / (m_font.line_height * m_font.font_size));
        line_number = std::min(line_number, int(m_lines.size()));

        int char_number = std::floor(pos.x / m_font.advance);
        char_number = std::min(char_number, int(m_lines[line_number].length()));

        return { float(char_number), float(line_number) };
    }

    vec2 get_dims() {return {m_text_width_height.x * m_font.advance, m_font.line_height * m_font.font_size * m_lines.size()};}

    Text(char * file_name) : m_font{0, 0} {
        m_file.open(file_name);
        std::string line;
         if (m_file.is_open()) {
            while (getline(m_file, line)) {
                m_lines.push_back(line);
                m_text_width_height.x = std::max(size_t(m_text_width_height.x), line.size());
            }
            
            m_file.close();
        }
    }
    ~Text() {}

    void Render(vec2 start_pos) {
        start_pos = dimension_to_idx(start_pos);
        start_pos.floor();

        for(int i = start_pos.y; i < std::min(size_t(start_pos.y + m_cols_rows.y+1), m_lines.size()); i++) {
            vec2 pos = idx_to_dimension(vec2(0, i));

            // for(const auto & the_char : m_lines[i]) {
            //     pos.x = gfx::render_char(the_char, pos, gfx::sFont("consola", m_font.font_size));
            // }
            gfx::render_line(m_lines[i], pos, gfx::sFont("consola", m_font.font_size));
        }
    }

    void onClick(vec2 pos) {}

    void onResize(int width, int height) {
        m_window_dims = {width, height};

        m_cols_rows = dimension_to_idx(m_window_dims);
        m_cols_rows.floor();
    }

    void onFontUpdate(const sDocumentFont & font) {m_font = font;}
};