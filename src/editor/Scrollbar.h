#pragma once
#include <gfx/lib_gfx.h>
#include <utilities/data_types.h>

// Scrollbar Abstract base class
class Scrollbar {
protected:
    vec2 m_pos;
    bool m_active;

public:
    Scrollbar() : m_pos({0, 0}) {}
    virtual void Render(const vec2 & cur_dim, const vec2 &  max_dim) = 0;
    virtual void onClick(vec2 pos) = 0;
};

class HightScrollBar : public Scrollbar {
public:
    void set_position(vec2 pos) { this->m_pos = pos; }

    virtual void Render(const vec2 & cur_dim, const vec2 & max_dim) override {
        if(cur_dim.y <= max_dim.y) return;

        static float bar_width = 20;
        gfx::render_square(max_dim.x - bar_width, m_pos.y, bar_width, (max_dim.y / cur_dim.y) * max_dim.y, {0xFF, 0xFF, 0xFF, 0x55});
    }

    virtual void onClick(vec2 pos) override {

    }

};

class WidthScrollBar : public Scrollbar {
public:
    void set_position(vec2 pos) { this->m_pos = pos; }

    virtual void Render(const vec2 & cur_dim, const vec2 & max_dim) override {
        if(cur_dim.x <= max_dim.x) return;

        static float bar_height = 20;
        gfx::render_square(m_pos.x, max_dim.y - bar_height, (max_dim.x / cur_dim.x) * max_dim.x, bar_height, {0xFF, 0xFF, 0xFF, 0x55});
    }

    virtual void onClick(vec2 pos) override {
        
    }

};

class FullScrollBar : public Scrollbar {
private:
    HightScrollBar m_height;
    WidthScrollBar m_width;
    vec2 m_pos;
public:
    FullScrollBar() : Scrollbar(), m_pos{0, 0} {}

    virtual void Render(const vec2 &  cur_dim, const vec2 & max_dim) override {
        m_height.set_position(m_pos);
        m_width.set_position(m_pos);
 
        m_height.Render(cur_dim, max_dim);
        m_width.Render(cur_dim, max_dim);

        gfx::move_text_window(vec2(m_pos.x, m_pos.y));
    }

    virtual void onClick(vec2 pos) override {
        
    }
};

