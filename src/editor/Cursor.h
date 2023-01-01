#pragma once
#include <gfx/lib_gfx.h>
#include <utilities/data_types.h>
#include <editor/settings.h>

class Cursor {
protected:
    vec2 m_dims;
    int m_cursor_number_frame;
    bool m_render_cursor;
public:
    Cursor() : m_dims({1.0f, FONT_SIZE}), m_cursor_number_frame(0), m_render_cursor(false) {}

    // Pos: in the index of the char number pos.x in the line number pos.y
    virtual void Render(vec2 pos) = 0;
};

class NormalCursor : public Cursor {
public:
    virtual void Render(vec2 pos) override {

        // if(--m_cursor_number_frame < 0) {
        //     m_cursor_number_frame = CURSOR_RENDER_FRAME;
        //     m_render_cursor = !m_render_cursor;
        // }
        // if(m_render_cursor)
        //     gfx::render_square(pos.x, pos.y, m_dims.x, m_dims.y, {0xFF, 0xFF, 0xFF, 0xFF});
        gfx::render_square(pos.x, pos.y, m_dims.x, m_dims.y, {0xFF, 0xFF, 0xFF, 0xFF});
    }
};