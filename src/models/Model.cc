#include "Model.h"

/***Model*************************************/
Model::Model(float x, float y, float size, sColor color)
    : x(x), y(y), size(size), m_color(color) {}


void Model::wrap_coords() {
    // float ix = this->m_pos.x;
    // float iy = this->m_pos.y;

    // if (ix < 0) m_pos.x = 0;
    // if (iy < 0) m_pos.y = 0;
    // if (ix > max_player_x) m_pos.x = max_player_x;
    // if (iy > max_player_y) m_pos.y = max_player_y;
}