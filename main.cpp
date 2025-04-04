/*
Contains the main function and sets up the OpenGL context, shaders, and rendering loop.
Initializes the OpenGL context and libraries (e.g., GLFW, GLEW).
Compiles and links vertex and fragment shaders.
Creates and configures VAOs and VBOs with vertex data.
Continuously renders frames, handling input, error and updating the scene.
Cleans up resources (e.g., shaders, VAOs, VBOs) before exiting.
*/

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>	
#include<stb/stb_image.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//think shaders as function for GPU

const unsigned int width = 800;
const unsigned int height= 800;

/*
	make vertices
*/
//special float for GL compatibility
//specify coords, each represent 3 point(x,y,z) in vertices
//opengl will auto interpolate color gradient
//specify how we want to map the texture on the vertices (higher than 1 cause tiling)
//Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};



//GLfloat vertices[] =
//{ //     COORDINATES     /        COLORS      /		TexCoord
//	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,// Lower left corner
//	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,// Upper left corner
//	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,// Upper right corner
//	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f // Lower right corner
//};

//triangle
//GLfloat vertices[] =
//{ //               COORDINATES					/     COLORS				//
//	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.6f,  0.04f,	// Lower left corner
//	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.71f, 0.59f,  0.84f,  // Lower right corner
//	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.71f, 0.59f,  0.84f,  // Upper corner
//	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.2f, 0.71f, 0.67f,	// Inner left
//	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.71f, 0.59f,  0.84f,  // Inner right
//	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.2f, 0.71f, 0.67f		// Inner down
//};


//tell openGL to draw 3 points together to form a triangle faces in the order specified here
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

//GLuint indices[] =
//{
//	0, 2, 1,	//upper triangle face
//	0, 3, 2		//lower triangle faces
//};


int main() {

	glfwInit();

	//Context of GLFW version and package we are using (3.3 Core)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//windows param(height, width, title, FullScreen, not important), check if null and request to use window
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLForFun", NULL, NULL);
	if (window == NULL) {
		std::cout << "Fail to create Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);


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

	// Links VBO attributes such as coordinates, colors, texture to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	// unbind EBO after unbind VAO
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	/*
		talks w/ the GL uniform variables that talks with shaders
	*/
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	/*
		image handling block.
		First define the properties and store the image,
		Then we assign the texture into a texture unit (slots of texture in a texture bundle, 16 each)
		which allow fragment shader to work w/ the textures in the bundle at the same time,
		Then we set the parameter of the picture that we want,
		Then generate the texture, its mipmap and delete image data
	*/
	//defining height, width in pixels and color channel of an image
	//and flip image cuz stb read from top left but opengl read from bottom left
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);

	//storing image in array of byte
	unsigned char* bytes = stbi_load("towa.jpeg", &widthImg, &heightImg, &numColCh, 0);

	GLuint textures;

	//generate the texture object (num of texture, pointer)
	//remember to delete at the end
	glGenTextures(1, &textures);

	//to bind textures into a texture unit in a bundle
	//by making a bundle active and bind it
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures);

	//changing the filter of our texture to linear
	//modify the parameter of the texture (type, the parameter of the tex, the value we want to set)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//changing the tiling of our texture
	//S is for x-axis and T for y-axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//if you want to set 'clamp to border' mus also add this border color
	// float flatColor = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTextParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	//generaste the texture
	// type of tex, 0, color channel type we want, width, height, *legacy code, color channel of our image, 
	// data type of our pixel, image data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

	//generate mipmap (smaller res of the image)
	glGenerateMipmap(GL_TEXTURE_2D);

	//to delete the texture since we already convert image data into texture
	//and unbind the texture
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	//fetch our texture uniform, activate our shader program
	//and assign the uniform the index of our texture bundle, 0
	GLuint tex0uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0uni, 0);




	/*
		Main loop of our program
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


		/*
			For 3d projection

			local coord + (model matrix) -> world coord + (view matrix) ->
			view coord + (proj matrix) -> clip coord -> screen coord

			set the variable matrix equal to an identity matrix bcz OG matrix is zero matrix
			set all matrix use for transformation,
			we move the our camera view coord using glm::translate since all our coord is the same
		*/
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		//move the coord (matrix to move, vec3 xyz of how much to move (+ is towards us))
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		
		//to set our projection matrix(fov, aspect ratio, closest & farthest focal length)
		proj = glm::perspective(glm::radians(45.04f), (float)(width / height), 0.1f, 100.0f);

		//assign value of our matrices using uniform locator
		//then send matrices to the active shaders
		//use value ptr to point at the value instead of metadata
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		//to give the uniID a value
		//must be after activate
		glUniform1f(uniID, 0.5f);

		//bind the texture object
		glBindTexture(GL_TEXTURE_2D, textures);

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
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
	glDeleteTextures(1, &textures);
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}