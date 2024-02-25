#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

// The triangle point
GLfloat vertices[] = {

	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left Corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Inner down
};

GLuint indices[] = {

	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};


int main() {

	// Initialize glfw
	glfwInit();

	// Tpecified the open gl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Told glfw that I wish to use modern commands only
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window with size WINDOW_WIDTH x WINDOW_HEIGHT and a title 3DGameEngine while not being full screen
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3DGameEngine", NULL, NULL);
	
	// Checking if action was able to complete otherwise no need to countine without a window
	if (window == NULL) {

		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Telling glfw that I wish to show the window I created
	glfwMakeContextCurrent(window);

	// Initialize glad
	gladLoadGL();

	// Specified the sizes of the area which I wish to effect (in this case all of it)
	glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Generate the shaders with the files defualt.vert and defualt.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Creating the vertex array object (the communication between the cpu and gpu) and bind it
	VAO VAO1;
	VAO1.Bind();

	// Creating the Vertex buffer object (the points of the triangles) and the element buffer (the order in which to draw)
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Sending the data from cpu to gpu
	VAO1.LinkVBO(VBO1, 0);
	
	// unbinding all to prevent accidental changing
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Waiting while the window is not closed
	while (!glfwWindowShouldClose(window)) {

		// changing the color of the buffer to black with no transpernicy
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Telling opengl I wish to use the shader program I created
		shaderProgram.Activate();
		// Telling opengl I wish to the VAO I created
		VAO1.Bind();
		// Drawing the triangle with the opengl triangles
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		// Refreshing the window so it won't be stuck
		glfwPollEvents();
	}

	// Deleting VAO, VBO, and the shader program
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destroying the window
	glfwDestroyWindow(window);

	// Terminating glfw
	glfwTerminate();
	return 0;
}