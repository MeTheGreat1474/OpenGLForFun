/*
Manages the state needed to specify vertex data for rendering.
Specifies the layout of vertex data (e.g., positions, colors) using vertex attribute pointers.

VAO and VBO work together to manage and provide vertex data to the GPU.
The VAO stores the state of vertex attribute pointers, while the VBO stores the actual vertex data.
*/

#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();

	//communicate w/ vertex shader from outside
	//layout - 0 for position, 1 for color
	//numComp - 3 per layout
	//type - GL float
	//stride - distance between 1 vertex and another
	//offset - offset where start
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}