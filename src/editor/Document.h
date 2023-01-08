#pragma once

#include <string>
#include <gfx/lib_gfx.h>
#include <utilities/error.h>
#include <utilities/data_types.h>
#include <editor/settings.h>
#include <editor/Scrollbar.h>
#include <editor/Text.h>
#include <editor/Cursor.h>

class Document {
public:
    Document(char * file_name) : m_text(file_name), m_font{FONT_SIZE, LINE_HEIGHT}, m_should_render(2) {
        m_text.onFontUpdate(m_font);

        m_window_dim = gfx::window_dims();
        m_text.onResize(m_window_dim.x, m_window_dim.y);
        m_scrollbar.onResize(m_window_dim.x, m_window_dim.y);
        
        m_text_dim = m_text.get_dims();
    }

    void Render() {
        if(!m_should_render) return;
        m_should_render =  m_should_render >> 1;
        gfx::window_clear();
        m_scrollbar.Render(m_text_dim);
        m_text.Render(m_view_pos);
        m_cursor.Render(m_text.idx_to_dimension(m_cursor_pos) - m_view_pos);
    }

    void onClick(vec2 click_pos) {
        this->force_render();

        if(this->m_scrollbar.onClick(click_pos)) return;

        this->m_text.onClick(click_pos);
        m_cursor_pos = m_text.get_cursor_idx(click_pos + m_view_pos);
    }

    void onResize(int width, int height) {
        this->force_render();

        m_window_dim = {width, height};
        m_text.onResize(width, height);
        m_scrollbar.onResize(width, height);
    }

    void onHoldAndMove(Mouse e) {
        this->force_render();

        this->m_scrollbar.onHoldAndMove(vec2({e.dx, e.dy}));
        m_view_pos = m_scrollbar.get_position();

        m_view_pos.x *= m_text_dim.x / m_window_dim.x;
        m_view_pos.y *= m_text_dim.y / m_window_dim.y;

    }

    void onWrite(char ch) {
        this->force_render();

        m_text.onWrite(m_cursor_pos, ch);
        m_text_dim = m_text.get_dims();
        scroll_to_cursor();
    }

    void onNewLine() {
        this->force_render();

        m_text.onNewLine(m_cursor_pos);
        m_text_dim = m_text.get_dims();
        scroll_to_cursor();
    }

    void onRemove() {
        this->force_render();
        m_text.onRemove(m_cursor_pos);
        m_text_dim = m_text.get_dims();
        scroll_to_cursor();
    }

    void onMoveCursor(uint32_t dir) {
        this->force_render();
        m_text.onMoveCursor(m_cursor_pos, dir);
        scroll_to_cursor();
    }
    
    ~Document() {}

private:
    void force_render() {m_should_render = 2;}
    void scroll_to_cursor() {
       vec2 cursor_pos = m_text.idx_to_dimension(m_cursor_pos) - m_view_pos;
        if(cursor_pos.x < 0) {
            m_scrollbar.onForceScroll({cursor_pos.x, 0});
        } else if (cursor_pos.x > m_window_dim.x) {
            m_scrollbar.onForceScroll({cursor_pos.x - m_window_dim.x * 0.95, 0});
        }

        if(cursor_pos.y < 0) {
            m_scrollbar.onForceScroll({0, cursor_pos.y});
        } else if (cursor_pos.y >= m_window_dim.y) {
            m_scrollbar.onForceScroll({0, cursor_pos.y - m_window_dim.y * 0.95});
        }

        m_view_pos = m_scrollbar.get_position();
        m_view_pos.x *= m_text_dim.x / m_window_dim.x;
        m_view_pos.y *= m_text_dim.y / m_window_dim.y;
    }

private:
    FullScrollBar m_scrollbar;
    NormalCursor m_cursor;
    Text m_text;
    sDocumentFont m_font;
    vec2 m_view_pos,    // Position of the scroll bars initially should be 0,0
         m_cursor_pos,   // Mouse Line number and position in the line
         m_window_dim,
         m_text_dim;
    uint8_t m_should_render;
};
