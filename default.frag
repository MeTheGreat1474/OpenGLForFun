/*
This file contains a fragment shader written in GLSL.
The fragment shader is responsible for determining the color of each pixel.

default.frag works with default.vert to complete the shader program.
vertex shader passes color data to the fragment shader, 
which then determines the final pixel color.
*/

#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;


void main()
{
	FragColor = vec4(color, 1.0f);
}