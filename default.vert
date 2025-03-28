/*
This file contains a vertex shader written in GLSL (OpenGL Shading Language).
The vertex shader is responsible for processing each vertex's position and color data.
It provides vertex data (positions and colors) to the vertex shader 
via vertex buffer objects (VBOs) and vertex array objects (VAOs).

default.frag works with default.vert to complete the shader program.
vertex shader passes color data to the fragment shader, 
which then determines the final pixel color.
*/

#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;


// Outputs the color for the Fragment Shader
out vec3 color;

//dont define uniform if u dont use it
// Controls the scale of the vertices
uniform float scale;


void main()
{
	// Outputs the positions/coordinates + scales of all vertices
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);

	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
}