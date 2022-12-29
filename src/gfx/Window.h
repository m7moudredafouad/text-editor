#pragma once

#include <gfx/gfx.h>

/**
 * @brief Singleton Window
 * 
 */

struct Keyboard {
    int key, scancode, action, mods;
};

struct Mouse{
    int key, action, mods;
    float x, y, dx, dy;
};

struct WindowSize {
    int width, height;
};

class Window {
private:
    static GLFWwindow* m_window;
    static uint32_t m_width, m_height;
    static float m_mouse_x, m_mouse_y;
    static double m_delta_time, m_last_time;

public:     // Static Public Functions
    static std::queue<Keyboard> keys;
    static std::queue<Mouse> mouse;
    static std::queue<WindowSize> window_size;
    static Window & getInstance();
    static float width() {return (float)Window::m_width;}
    static float height() {return (float)Window::m_height;}
    static float mouse_x() {return Window::m_mouse_x;}
    static float mouse_y() {return Window::m_mouse_y;}
    static float ratio() {return (float)Window::m_width / (float) Window::m_height;}
    static float delta_time() {return (float)m_delta_time;}

private:    // Static Private Functions
    static void _handle_resize(GLFWwindow* window, int width, int height);
    static void _handle_key(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void _handle_mouse_pos(GLFWwindow* handle, double x, double y);
    static void _handle_mouse_key(GLFWwindow* handle, int button, int action, int mods);

private:    // Private Functions
    Window();
    Window(const Window &) = delete;
public:
    void create(const char * name, uint32_t width=1024, uint32_t height=768);
    void loop(void (*init)(void), void (*render)(void), void (*destroy)(void));

    ~Window();
};  // class Window





