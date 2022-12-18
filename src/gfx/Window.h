#pragma once

#include "gfx.h"
#include <vector>

/**
 * @brief Singleton Window
 * 
 */

struct Button {
    double delta;
    bool down;
};

struct Keyboard {
    Button keys[1024];
};

struct Mouse{
    Button keys[GLFW_MOUSE_BUTTON_LAST];
    float x, y, dx, dy,delta_time;
};

typedef void(*KEY_Handler)(const Keyboard &);

class Window {
private:
    static GLFWwindow* m_window;
    static uint32_t m_width, m_height;
    static double m_delta_time, m_last_time;

public:     // Static Public Functions
    static Keyboard keyboard;  // TODO: Move from here
    static Mouse mouse;  // TODO: Move from here
    static Window & getInstance();
    static float width() {return (float)Window::m_width;}
    static float height() {return (float)Window::m_height;}
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
    void create(const char * name="Game", uint32_t width=1024, uint32_t height=768);
    void loop(void (*init)(void), void (*render)(void), void (*destroy)(void));

    ~Window();
};  // class Window





