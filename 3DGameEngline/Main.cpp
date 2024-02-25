#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800


// Vertex shader Source code
const char* vertexShaderource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment shader Source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0";


int main() {

	// Initialize glfw
	glfwInit();

	// Tpecified the open gl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Told glfw that I wish to use modern commands only
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// The triangle point
	GLfloat vertices[] = {

		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left Corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) / 2, 0.0f, // Upper corner
	};


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

	// Create Vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Add the code for the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderource, NULL);

	// Compile the code
	glCompileShader(vertexShader);

	// Create Fragment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Add the code for the Fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	// Compile the code
	glCompileShader(fragmentShader);


	// Create shader program object
	GLuint shaderProgram = glCreateProgram();

	// Add the shaders to the shader program object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link the shaders together in the shader program object
	glLinkProgram(shaderProgram);

	// Delete the shader objects since they are already added and linked in the shader program object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create vertex array object (VAO) and vertex buffer object (VBO) to send data from cpu to gpu
	GLuint VAO, VBO;

	// Generate the VAO and VBO with only 1 object since we only have a triangle
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Set the VAO of this program to VAO
	glBindVertexArray(VAO);

	// Set the VBO as the GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Add the triangle data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Making the data in the VBO readable by openGl
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// Binding VBO and VAO to 0 to stop us from accidentally modifying VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Changing the color of the buffer to black with no transpernicy
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Swapping the front buffer with the front one
	glfwSwapBuffers(window);

	// Waiting while the window is not closed
	while (!glfwWindowShouldClose(window)) {

		// changing the color of the buffer to black with no transpernicy
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Telling opengl I wish to use the shader program I created
		glUseProgram(shaderProgram);
		// Telling opengl I wish to the VAO I created
		glBindVertexArray(VAO);
		// Drawing the triangle with the opengl triangles
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		// Refreshing the window so it won't be stuck
		glfwPollEvents();
	}

	// Deleting VAO, VBO, and the shader program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Destroying the window
	glfwDestroyWindow(window);

	// Terminating glfw
	glfwTerminate();
	return 0;
}