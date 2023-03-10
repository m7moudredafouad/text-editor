#pragma once
#include <gfx/lib_gfx.h>
#include <utilities/data_types.h>

// Scrollbar Abstract base class
class Scrollbar {
protected:
    vec2 m_dims,    // Bars dimensions
         m_pos,     // Bars Position
         m_window_dims, // Window Dimension
         m_last_click_pos;  // Last Click Position

    bool m_active, // Did the user click on the bar and activated it ?
         m_rendered; // Is the bar rendered or not ?
public:
    Scrollbar() : m_dims({20, 20}), m_pos({0, 0}),
                    m_window_dims({0, 0}), m_last_click_pos({0, 0}),
                    m_active(false), m_rendered(false) {}

    virtual void Render(const vec2 & cur_dim) = 0;
    virtual bool onClick(vec2 pos) = 0;
    virtual void onResize(int width, int height) = 0;
    virtual void onHoldAndMove(vec2 delta) = 0;
    virtual void onForceScroll(vec2 delta) = 0;
};

class HightScrollBar : public Scrollbar {
public:
    vec2 get_position() { return this->m_pos; }

    virtual void Render(const vec2 & cur_dim) override {
        if(cur_dim.y <= m_window_dims.y) {
            m_rendered = false;
            m_pos = {0, 0};
            return;
        }

        m_rendered = true;   
        m_dims.y = (m_window_dims.y / cur_dim.y) * m_window_dims.y;

        gfx::render_square(m_window_dims.x - m_dims.x, m_pos.y, m_dims.x, m_dims.y, {0xFF, 0xFF, 0xFF, 0x55});
    }

    virtual bool onClick(vec2 pos) override {
        m_last_click_pos = pos;
        return m_active = m_rendered && (pos.x >= m_window_dims.x - m_dims.x);
    }

    virtual void onResize(int width, int height) {
        m_window_dims = {width, height};
    }

    virtual void onHoldAndMove(vec2 delta) override {
        if(!m_active) return;
        if(m_last_click_pos.x >= m_window_dims.x - m_dims.x)
            this->onForceScroll(delta);
        
    }

    virtual void onForceScroll(vec2 delta) {
        m_pos.y += delta.y;
        if(m_pos.y < 0) m_pos.y = 0;
        if(m_pos.y > m_window_dims.y - m_dims.y) m_pos.y = m_window_dims.y - m_dims.y;
    }

};

class WidthScrollBar : public Scrollbar {
public:
    vec2 get_position() { return this->m_pos; }

    virtual void Render(const vec2 & cur_dim) override {
        if(cur_dim.x <= m_window_dims.x) {
            m_rendered = false;
            m_pos = {0, 0};
            return;
        }

        m_rendered = true;   
        m_dims.x = (m_window_dims.x / cur_dim.x) * m_window_dims.x;

        gfx::render_square(m_pos.x, m_window_dims.y - m_dims.y, m_dims.x, m_dims.y, {0xFF, 0xFF, 0xFF, 0x55});
    }

    virtual bool onClick(vec2 pos) override {
        m_last_click_pos = pos;
        return m_active = m_rendered && (pos.y >= m_window_dims.y - m_dims.y);
    }

    virtual void onResize(int width, int height) {
        m_window_dims = {width, height};
    }

    virtual void onHoldAndMove(vec2 delta) override {
        if(!m_active) return;
        if(m_last_click_pos.y >= m_window_dims.y - m_dims.y)
            this->onForceScroll(delta);
    }

    virtual void onForceScroll(vec2 delta) {
        m_pos.x += delta.x;

        if(m_pos.x < 0) m_pos.x = 0;
        if(m_pos.x > m_window_dims.x - m_dims.x) m_pos.x = m_window_dims.x - m_dims.x;
    }
};

class FullScrollBar : public Scrollbar {
private:
    HightScrollBar m_height;
    WidthScrollBar m_width;
public:
    FullScrollBar() : Scrollbar() {}

    vec2 get_position() { return this->m_pos; }

    virtual void Render(const vec2 & cur_dim) override {
        m_height.Render(cur_dim);
        m_width.Render(cur_dim);

        gfx::move_text_window(vec2(m_pos.x * cur_dim.x / m_window_dims.x, -m_pos.y * cur_dim.y / m_window_dims.y));
    }

    virtual bool onClick(vec2 pos) override {
        return this->m_height.onClick(pos) || this->m_width.onClick(pos);
    }

    virtual void onResize(int width, int height) {
        m_window_dims = {width, height};
        this->m_height.onResize(width, height);
        this->m_width.onResize(width, height);
    }

    virtual void onHoldAndMove(vec2 delta) override {
        this->m_height.onHoldAndMove(delta);
        this->m_width.onHoldAndMove(delta);

        auto h_pos = this->m_height.get_position();
        auto w_pos = this->m_width.get_position();

        this->m_pos = vec2({w_pos.x, h_pos.y});
    }

    virtual void onForceScroll(vec2 delta) {
        this->m_height.onForceScroll(delta);
        this->m_width.onForceScroll(delta);

        auto h_pos = this->m_height.get_position();
        auto w_pos = this->m_width.get_position();

        this->m_pos = vec2({w_pos.x, h_pos.y});
    }

};

