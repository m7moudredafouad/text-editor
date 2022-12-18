#pragma once
#include <vector>
#include "Texture.h"


struct sVertex {
    float pos[2];
    float texture_cord[2];
};

class Char {
    sVertex points[6];
public:
    Char(float xpos, float ypos, float h, float w):
    points{
        {{xpos, ypos + h},      {0.0f, 0.0f}},            
        {{xpos, ypos},          {0.0f, 1.0f}},
        {{xpos + w, ypos},      {1.0f, 1.0f }},

        {{xpos, ypos + h},      {0.0f, 0.0f }},
        {{xpos + w, ypos},      {1.0f, 1.0f }},
        {{xpos + w, ypos + h},  {1.0f, 0.0f }}  
    } {  }
};


struct Character {
    uint32_t TextureID; 
    uint32_t width, height;
    int32_t bitmap_left, bitmap_top, advance;
};

