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
    sGapBuffer(const std::string & buffer) : m_buffer(buffer){
        this->reset_gap();
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
            for(int i = idx; i < m_gap_idx; i++)
                m_buffer[i + m_gap_size] = m_buffer[i];
        } else {
            for(int i = m_gap_idx; i < idx; i++)
                m_buffer[i] = m_buffer[i + m_gap_size];
        }

        m_gap_idx = idx;
    }

    void insert(int idx, char ch) {
        idx = to_positive_idx(idx);
        if(!m_gap_size) this->reset_gap();

        move_gap_to(idx);
        m_buffer[idx] = ch;
        m_gap_idx++;
        m_gap_size--;
    }

    void insert(int idx, const std::string & buffer) {
        idx = to_positive_idx(idx);
        int buf_len = buffer.length();
        if(buf_len > m_gap_size) {
            m_buffer = this->get_buffer();
            m_buffer = m_buffer.substr(0, idx) + buffer + m_buffer.substr(idx+1, m_buffer.length());
            this->reset_gap();
        } else {
            move_gap_to(idx);
            for(int i = 0; i < buf_len; i++)
                m_buffer[idx+i] = buffer[i];
            m_gap_idx += buf_len;
            m_gap_size -= buf_len;
        }
    }

    void remove(int idx, uint32_t len) {
        idx = to_positive_idx(idx);
        move_gap_to(idx);
        m_gap_size += len;
    }

private:
void reset_gap() {
    m_gap_size = 100;
    m_gap_idx = m_buffer.length();
    m_buffer.resize(m_gap_idx + 100);
}

int to_positive_idx(int idx) {
    if(idx >= 0) return idx;
    return this->length() + idx;
}

private:
    std::string m_buffer;
    int m_gap_idx, m_gap_size;
};

struct sLine {
    sGapBuffer data;
    sLine *next, *prev;

    sLine() : data(sGapBuffer("")), next(nullptr), prev(nullptr) {}
    sLine(const std::string & data) : data(sGapBuffer(data)), next(nullptr), prev(nullptr) {}
    sLine(const std::string & data, sLine *next, sLine *prev) : data(sGapBuffer(data)), next(next), prev(prev) {}
};


class Text {
public:
    Text(char * file_name);
    ~Text();

    void Render(vec2 start_pos);
    void onClick(vec2 pos);
    void onWrite(vec2 & cursor_pos, char ch);
    void onNewLine(vec2 & cursor_pos);
    void onRemove(vec2 & cursor_pos);
    void onMoveCursor(vec2 & cursor_pos, uint32_t dir);

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
    uint32_t get_max_line_width();

private:
    std::vector<std::string> m_lines;
    std::ifstream m_file;
    sDocumentFont m_font;

    sLine *m_head, *m_tail;

    uint32_t m_max_chars, m_max_line; // The number of lines and max chars in a line.
    vec2 m_window_dims, // Window Dimension
         m_cols_rows; // The max cols and rows the the current window size can fit
};