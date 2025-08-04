#version 410 core

precision highp float;

in vec4 v_colors;

void main(){
    gl_FragColor = v_colors;
}