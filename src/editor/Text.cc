#include <editor/Text.h>

Text::Text(char * file_name) : m_max_chars(0), m_max_line(0), m_font{0, 0}, m_head(new sLine()), m_tail(new sLine()) {
    m_head->next = m_tail;
    m_tail->prev = m_head;

    m_file.open(file_name);
    std::string line;
        if (m_file.is_open()) {
        while (getline(m_file, line)) {
            // m_lines.push_back(line);
            this->push_back(line);
            m_max_chars = std::max(size_t(m_max_chars), line.size());
            m_max_line++;
        }

        if(!m_max_line) {
            m_max_line++;
            this->push_back("");
        }
        
        m_file.close();
    }
}
Text::~Text() {
    sLine * cur = m_head, *next;
    while (cur) {
        next = cur->next;
        delete cur;
        cur = next;
    }
}

vec2 Text::dimension_to_idx(const vec2 & pos) {
    return vec2 {
        pos.x / m_font.advance,
        pos.y / (m_font.line_height * m_font.font_size)
    };
}

vec2 Text::idx_to_dimension(const vec2 & pos) {
    return vec2 {
        m_font.advance * pos.x,
        m_font.font_size * m_font.line_height * pos.y
    };
}

vec2 Text::get_cursor_idx(const vec2 & pos) {
    uint32_t line_number = std::floor(pos.y / (m_font.line_height * m_font.font_size));
    line_number = std::min(line_number, m_max_line-1);

    uint32_t char_number = std::floor(pos.x / m_font.advance);
    char_number = std::min(char_number, uint32_t(this->get_line(line_number)->data.get_buffer().length()));

    return { float(char_number), float(line_number) };
}

void Text::Render(vec2 start_pos) {
    start_pos = dimension_to_idx(start_pos);
    start_pos.floor();
    
    sLine *cur_line = this->get_line(start_pos.y);

    for(int i = start_pos.y;
        i < std::min(uint32_t(start_pos.y + m_cols_rows.y+1), m_max_line) && cur_line && cur_line != m_tail;
        i++, cur_line = cur_line->next) {

        vec2 pos = idx_to_dimension(vec2(0, i));
        gfx::render_line(cur_line->data.get_buffer(), pos, gfx::sFont("consola", m_font.font_size));
    }
}

void Text::onClick(vec2 pos) {}

void Text::onWrite(vec2 & cursor_pos, char ch) {
    sLine *line = this->get_line(int(cursor_pos.y));

    line->data.insert(int(cursor_pos.x), ch);
    m_max_chars = std::max(size_t(m_max_chars), line->data.get_buffer().length());
    cursor_pos.x++;
}

void Text::onNewLine(vec2 & cursor_pos) {
    sLine *line = this->get_line(int(cursor_pos.y));

    std::string buf = line->data.get_buffer(cursor_pos.x);
    line->data.remove(int(cursor_pos.x), buf.length());

    this->insert_line(cursor_pos.y+1, buf);
    m_max_line++;
    cursor_pos.y++;
    cursor_pos.x = 0;
}

void Text::onRemove(vec2 & cursor_pos) {
    sLine *line = this->get_line(int(cursor_pos.y));

    if(int(cursor_pos.x) > 0) {
        int data_len = line->data.length();
        line->data.remove(int(cursor_pos.x) - 1, 1);
        if(data_len == m_max_chars) m_max_chars = get_max_line_width();
        cursor_pos.x--;
    } else {
        int prev_data_len = line->prev->data.length();

        line->prev->data.insert(prev_data_len, line->data.get_buffer());
        line->prev->next = line->next;
        line->next->prev = line->prev;
        delete line;

        cursor_pos.x = prev_data_len;
        cursor_pos.y--;
        m_max_line--;
        m_max_chars = get_max_line_width();
    }
}

void Text::onMoveCursor(vec2 & cursor_pos, uint32_t dir) {
    sLine *line = this->get_line(int(cursor_pos.y));
    sLine *prev = line->prev == m_head ? nullptr : line->prev;
    sLine *next = line->next == m_tail ? nullptr : line->next;
    switch (dir) {
    case 0: // Right
        if(cursor_pos.x < line->data.length()) {
            cursor_pos.x++;
            return;
        }

        if(next) {
            cursor_pos.y++;
            cursor_pos.x = 0;
        }
        break;
    case 1: // Left
        if(cursor_pos.x > 0) {
            cursor_pos.x--;
            return;
        }

        if(prev) {
            cursor_pos.y--;
            cursor_pos.x = prev->data.length();
        }
        break;
    case 2: // Down
        if(!next) return;
        cursor_pos.y++;
        cursor_pos.x = std::min(uint32_t(cursor_pos.x), next->data.length());
        break;
    case 3: // Up
        if(!prev) return;
        cursor_pos.y--;
        cursor_pos.x = std::min(uint32_t(cursor_pos.x), prev->data.length());
        break;
    default:
        break;
    }
}

void Text::onResize(int width, int height) {
    m_window_dims = {width, height};

    m_cols_rows = dimension_to_idx(m_window_dims);
    m_cols_rows.floor();
}

void Text::push_back(const std::string & line) {
    sLine *new_line = new sLine(line, m_tail, m_tail->prev);
    m_tail->prev->next = new_line;
    m_tail->prev = new_line;
}

void Text::insert_line(int idx, const std::string & line) {
    if(m_max_line == 0 || m_max_line == idx) {
        this->push_back(line);
        return;
    }

    sLine *line_in_idx = get_line(idx);
    sLine *new_line = new sLine(line, line_in_idx, line_in_idx->prev);

    line_in_idx->prev->next = new_line;
    line_in_idx->prev = new_line;
}

sLine * Text::get_line(int idx) {
    ASSERT(idx >= 0 && uint32_t(idx) < m_max_line, "The given line index doesn't exist");

    sLine *target = m_head->next;

    while(target && --idx >= 0) target = target->next;
    ASSERT(target != nullptr && target != m_tail, "The given line index doesn't exist");

    return target;
}

uint32_t Text::get_max_line_width() {
    uint32_t len = 0;
    sLine *target = m_head->next;

    while(target != m_tail) {
        len = std::max(len, target->data.length());
        target = target->next;
    }

    return len;
}