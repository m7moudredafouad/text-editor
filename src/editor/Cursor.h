#pragma once
#include <gfx/lib_gfx.h>
#include <utilities/data_types.h>
#include <editor/settings.h>

class Cursor {
protected:
    vec2 m_dims;
public:
    Cursor() : m_dims({2.0f, FONT_SIZE}) {}

    // Pos: in the index of the char number pos.x in the line number pos.y
    virtual void Render(vec2 pos) = 0;
};

class NormalCursor : public Cursor {
public:
    virtual void Render(vec2 pos) override {

        pos.x = pos.x * 9 + START_X;

        pos.y = pos.y * LINE_HEIGHT * FONT_SIZE + START_Y + (LINE_HEIGHT - 1) * FONT_SIZE / 2;
        gfx::render_square(pos.x, pos.y, m_dims.x, m_dims.y, {0xFF, 0xFF, 0xFF, 0xFF});
    }
};