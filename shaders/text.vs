#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec4 color;

uniform mat4 projection;

out vec4 v_Color;
out vec2 v_TexCoords;

void main() {
    gl_Position = projection * vec4(pos, 0.0, 1.0);
    v_Color = vec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 1.0);
    v_TexCoords = TexCoords;

}