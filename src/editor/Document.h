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
private:
    FullScrollBar m_scrollbar;
    NormalCursor m_cursor;
    Text m_text;
    sDocumentFont m_font;
    vec2 m_view_pos,    // Position of the scroll bars initially should be 0,0
         m_cursor_pos,   // Mouse Line number and position in the line
         m_window_dim,
         m_text_dim;

public:
    Document(char * file_name) : m_text(file_name), m_font{FONT_SIZE, LINE_HEIGHT} {
        m_text.onFontUpdate(m_font);

        m_window_dim = gfx::window_dims();
        m_text.onResize(m_window_dim.x, m_window_dim.y);
        m_scrollbar.onResize(m_window_dim.x, m_window_dim.y);
        
        m_text_dim = m_text.get_dims();
    }

    void Render() {
        m_scrollbar.Render(m_text_dim);
        m_text.Render(m_view_pos);
        m_cursor.Render(m_text.idx_to_dimension(m_cursor_pos) - m_view_pos);
    }

    void onClick(vec2 click_pos) {
        if(this->m_scrollbar.onClick(click_pos)) return;

        this->m_text.onClick(click_pos);
        m_cursor_pos = m_text.get_cursor_idx(click_pos + m_view_pos);

        std::cout << m_cursor_pos.x << "\t" << m_cursor_pos.y << std::endl; 
    }

    void onResize(int width, int height) {
        m_window_dim = {width, height};
        m_text.onResize(width, height);
        m_scrollbar.onResize(width, height);
    }

    void onHoldAndMove(Mouse e) {
        this->m_scrollbar.onHoldAndMove(vec2({e.dx, e.dy}));
        m_view_pos = m_scrollbar.get_position();

        m_view_pos.x *= m_text_dim.x / m_window_dim.x;
        m_view_pos.y *= m_text_dim.y / m_window_dim.y;

    }

    void onWrite(char ch) {
        std::cout << ch;
    }
    
    ~Document() {}
};
