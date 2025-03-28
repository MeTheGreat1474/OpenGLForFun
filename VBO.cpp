/*
Stores vertex data in GPU memory.
Uploads vertex data (e.g., positions, colors) to the GPU.

VAO and VBO work together to manage and provide vertex data to the GPU.
The VAO stores the state of vertex attribute pointers, while the VBO stores the actual vertex data.
*/

#include"VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	//to store: (buffer type, total size, the data, uses of data) 
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}