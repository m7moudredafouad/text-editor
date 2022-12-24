#pragma once

#include <string>
#include <gfx/lib_gfx.h>
#include <utilities/error.h>
#include <utilities/data_types.h>
#include <editor/settings.h>
#include <editor/Scrollbar.h>
#include <editor/Text.h>

class Document {
private:
    Text m_text;
    FullScrollBar m_scrollbar;
public:
    Document(char * file_name) : m_text(file_name) {}

    void Render() {
        m_text.Render();
        m_scrollbar.Render(m_text.get_dims(), gfx::window_dims());
    }

    void onClick(vec2 click_pos) {
        this->m_scrollbar.onClick(click_pos);
    }

    void onHoldAndMove(Mouse e) {
        this->m_scrollbar.onHoldAndMove(vec2({e.dx, e.dy}));
    }

    void onWrite(char ch) {
        std::cout << ch;
    }
    
    ~Document() {}
};
