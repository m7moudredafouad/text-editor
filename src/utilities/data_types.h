#pragma once


struct vec2 {
    float x, y;
    vec2() : x(0), y(0) {}
    vec2(float x, float y) : x(x), y(y) {}

    vec2 operator+ (const vec2 & other) {
        return vec2(this->x + other.x, this->y + other.y);
    }

    vec2 & operator+= (const vec2 & other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    vec2 operator- (const vec2 & other) {
        return vec2(this->x - other.x, this->y - other.y);
    }

    vec2 & operator-= (const vec2 & other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }
};

struct sDocumentFont {
    uint32_t font_size, advance;
    float line_height;

    sDocumentFont(uint32_t size, float line_height) : font_size(size), advance((size / 2) + (1 + size / 20)), line_height(line_height) {}
};