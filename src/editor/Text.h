#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <gfx/lib_gfx.h>
#include <utilities/error.h>
#include <utilities/data_types.h>
#include <editor/settings.h>


struct sGapBuffer {
public:
    sGapBuffer(const std::string & buffer) : m_buffer(buffer), m_gap_idx(buffer.length()), m_gap_size(10){
        m_buffer.resize(buffer.length() + m_gap_size);
    }

    std::string get_buffer(int start_from = 0) {
        if(m_gap_idx == m_buffer.length() - m_gap_size) {
            return m_buffer.substr(start_from, m_gap_idx - start_from);
        }

        if(m_gap_idx == start_from) {
            return m_buffer.substr(start_from + m_gap_size, m_buffer.length() - m_gap_size - start_from);
        }

        return m_buffer.substr(start_from, m_gap_idx) +
               m_buffer.substr(start_from + m_gap_idx + m_gap_size, m_buffer.length() - m_gap_idx - m_gap_size - start_from);
    }

    uint32_t length() {
        return m_buffer.length() - m_gap_size;
    }

    void move_gap_to(int idx) {
        ASSERT(idx >= 0 && idx <= m_buffer.length() - m_gap_size, "Index must be with in range 0 and buffer size");

        if(idx == m_gap_idx) return;

        if(idx < m_gap_idx) {
            for(int i = m_gap_idx-1; i >= idx; i--){

                m_buffer[i + m_gap_size] = m_buffer[i];
                m_buffer[i] = '\0';
            }
        }

        m_gap_idx = idx;
    }

    void insert(int idx, char ch) {
        if(m_gap_size == 0) {
            m_gap_idx = m_buffer.length();
            m_buffer.resize(m_buffer.length() + 10);
            m_gap_size = 10;
        }

        move_gap_to(idx);
        m_buffer[idx] = ch;
        m_gap_idx++;
        m_gap_size--;

    }

    void insert(int idx, const std::string & buffer) {
        
    }

    void remove(int idx, uint32_t len) {
        move_gap_to(idx);
        m_gap_size += len;
    }

private:
    std::string m_buffer;
    int m_gap_idx, m_gap_size;
};

struct sLine {
    sGapBuffer data;
    sLine *next, *prev;

    sLine() : data(sGapBuffer("")), next(nullptr), prev(nullptr) {}
    sLine(sGapBuffer data) : data(data), next(nullptr), prev(nullptr) {}
    sLine(sGapBuffer data, sLine *next, sLine *prev) : data(data), next(next), prev(prev) {}
};


class Text {
public:
    Text(char * file_name);
    ~Text();

    void Render(vec2 start_pos);
    void onClick(vec2 pos);
    void onWrite(vec2 cursor_pos, char ch);
    void onNewLine(vec2 cursor_pos);
    void onRemove(vec2 cursor_pos);
    void onResize(int width, int height);

    vec2 dimension_to_idx(const vec2 & pos);
    vec2 idx_to_dimension(const vec2 & pos);
    vec2 get_cursor_idx(const vec2 & pos);

    void onFontUpdate(const sDocumentFont & font) {m_font = font;}
    vec2 get_dims() {return {m_max_chars * m_font.advance, m_font.line_height * m_font.font_size * m_max_line};}

private:
    void push_back(const std::string & line);
    void insert_line(int idx, const std::string & line);
    sLine *get_line(int idx);

private:
    std::vector<std::string> m_lines;
    std::ifstream m_file;
    sDocumentFont m_font;

    sLine *m_head, *m_tail;

    uint32_t m_max_chars, m_max_line; // The number of lines and max chars in a line.
    vec2 m_window_dims, // Window Dimension
         m_cols_rows; // The max cols and rows the the current window size can fit
};