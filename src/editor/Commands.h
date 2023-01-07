#pragma once
#include <editor/Document.h>
#include <gfx/lib_gfx.h>

/**
 * Command Interface
*/
class Command {
protected:
    std::shared_ptr<Document> m_doc;
public:
    Command(std::shared_ptr<Document> doc) :m_doc(doc) {}
    virtual void execute() = 0;
    virtual ~Command() {}
};

class NothingCommand : public Command {
public:
    NothingCommand(std::shared_ptr<Document> doc) :
        Command(doc) {}
    void execute() {}
};

/**
 * Commands from keyboard
*/
class WriteCommand : public Command {
private:
    Keyboard m_key;
public:
    WriteCommand(std::shared_ptr<Document> doc, Keyboard key) :
        Command(doc), m_key(key) {}

    void execute() {
        bool isAlpha = (m_key.key >= GLFW_KEY_A) && (m_key.key <= GLFW_KEY_Z);

        bool isSmall = (m_key.mods & GLFW_MOD_CAPS_LOCK) == (m_key.mods & GLFW_MOD_SHIFT);

        if(isAlpha && isSmall) m_key.key += 97 - 65;
        m_doc->onWrite(m_key.key);
    }
};

class NewLineCommand : public Command {
public:
    NewLineCommand(std::shared_ptr<Document> doc) :
        Command(doc) {}
    void execute() {
        m_doc->onNewLine();
    }
};

class RemoveCommand : public Command {
public:
    RemoveCommand(std::shared_ptr<Document> doc) :
        Command(doc) {}

    void execute() {
        m_doc->onRemove();
    }
};

class MoveCursorCommand : public Command {
private:
    uint32_t m_dir;
public:
    MoveCursorCommand(std::shared_ptr<Document> doc, uint32_t dir) :
        Command(doc), m_dir(dir) {}

    void execute() {
        m_doc->onMoveCursor(m_dir);
    }
};

/**
 * Commands from mouse
*/
class ClickCommand : public Command {
private:
    Mouse m_mouse;
public:
    ClickCommand(std::shared_ptr<Document> doc, Mouse mouse) : Command(doc), m_mouse(mouse) {}

    void execute() {
        if(m_mouse.dx || m_mouse.dy) {
            m_doc->onHoldAndMove(m_mouse);
        } else {
            m_doc->onClick(vec2({m_mouse.x, m_mouse.y}));
        }
    }
};

class ResizeCommand : public Command {
private:
    int m_width, m_height;
public:
    ResizeCommand(std::shared_ptr<Document> doc, int width, int height) :
        Command(doc), m_width(width), m_height(height) {}

    void execute() {
        m_doc->onResize(m_width, m_height);
    }
};