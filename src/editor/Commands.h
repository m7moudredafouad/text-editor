#pragma once
#include <editor/Document.h>
#include <gfx/lib_gfx.h>

class Command {
public:
    virtual void execute() = 0;    
};


class ClickCommand : public Command {
private:
    std::shared_ptr<Document> m_doc;
    Mouse m_mouse;
public:
    ClickCommand(std::shared_ptr<Document> doc, Mouse mouse) : m_doc(doc), m_mouse(mouse) {}

    void execute() {
        if(m_mouse.dx || m_mouse.dy) {
            m_doc->onHoldAndMove(m_mouse);
        } else {
            m_doc->onClick(vec2({m_mouse.x, m_mouse.y}));
        }
    }
};

class WriteCommand : public Command {
private:
    std::shared_ptr<Document> m_doc;
    Keyboard m_key;
public:
    WriteCommand(std::shared_ptr<Document> doc, Keyboard key) :
        m_doc(doc), m_key(key) {}

    void execute() {
        bool isAlpha = (m_key.key >= GLFW_KEY_A) && (m_key.key <= GLFW_KEY_Z);

        bool isSmall = (m_key.mods & GLFW_MOD_CAPS_LOCK) == (m_key.mods & GLFW_MOD_SHIFT);

        if(isAlpha && isSmall) m_key.key += 97 - 65;
        m_doc->onWrite(m_key.key);
    }
};