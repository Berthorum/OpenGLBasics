#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colors;

out vec4 v_colors;

void main(){
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
    v_colors = vec4(colors.r, colors.g, colors.b, 1.0f);
}