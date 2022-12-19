#version 330 core

in vec4 v_Color;
in vec2 v_TexCoords;

uniform sampler2D text;

out vec4 fragment_color;

void main() {
    if (v_Color.w == 0) discard;

    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, v_TexCoords).r);
    fragment_color = v_Color * sampled;
}