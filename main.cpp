#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>	

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//think shaders as function for GPU


/*
	make vertices
*/
//special float for GL compatibility
//specify coords, each represent 3 point(x,y,z) in vertices
//opengl will auto interpolate color gradient
//Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES					/     COLORS				//
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.6f,  0.04f,	// Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.71f, 0.59f,  0.84f,  // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.71f, 0.59f,  0.84f,  // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.2f, 0.71f, 0.67f,	// Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.71f, 0.59f,  0.84f,  // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.2f, 0.71f, 0.67f		// Inner down
};


//tell openGL to draw 3 points together to form a triangle in the order specified here
GLuint indices[] =
{
	0, 3, 5,	//lower left triangle
	3, 2, 4,	//lower right triangle
	5, 4, 1		//upper triangle
};

int main() {

	glfwInit();

	//Context of GLFW version and package we are using (3.3 Core)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//windows param(height, width, title, FullScreen, not important), check if null and request to use window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGLForFun", NULL, NULL);
	if (window == NULL) {
		std::cout << "Fail to create Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);


	/*
		Vertex Buffer Object (VBO) to store vertex.
		Vertex Array Object (VAO) points towards VBOs and tells Opengl how to intepret it.
		Index Buffer Array (EBO) to store order of drawing
	*/

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	//binding make a certain object into current object
	//so when that certain object is modified, the current is modified
	//VAO must be before VBO gen
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));


	/*
		tells opengl how to read vbo
	*/

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	// unbind EBO after unbind VAO
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	/*
		main loop of our program
	*/
	//only close window when 'X' button is pressed
	while (!glfwWindowShouldClose(window)) 
	{
		/*
			for displaying
		*/
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}


	/*
		to delete all object we created and terminate process
	*/
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}