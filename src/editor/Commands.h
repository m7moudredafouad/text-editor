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
public:
    ClickCommand(std::shared_ptr<Document> doc) : m_doc(doc) {}

    void execute() {
        m_doc->onClick();
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