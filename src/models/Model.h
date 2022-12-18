#pragma once

#include "./model_utils.h"

class Model {
    int x, y, size;
    sColor   m_color;
public:

    Model(float x, float y, float size, sColor color = { 0xFF, 0xFF, 0xFF, 0xFF });
    void wrap_coords();
};

