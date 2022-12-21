#version 330 core

in vec4 v_Color;
out vec4 fragment_color;

void main() {
    if (v_Color.w == 0) discard;
    fragment_color = v_Color;
}