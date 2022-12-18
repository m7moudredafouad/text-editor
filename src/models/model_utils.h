#pragma once

#include <gfx/Window.h>

struct sColor {
    float value[4];
    sColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : value{float(r), float(g), float(b), float(a)} {}
};
