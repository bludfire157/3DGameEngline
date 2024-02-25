#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

int main() {

	// Initialize glfw
	glfwInit();

	// specified the open gl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// told glfw that I wish to use modern commands only
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// create window with size WINDOW_WIDTH x WINDOW_HEIGHT and a title 3DGameEngine while not being full screen
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3DGameEngine", NULL, NULL);
	
	// checking if action was able to complete otherwise no need to countine without a window
	if (window == NULL) {

		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// telling glfw that I wish to show the window I created
	glfwMakeContextCurrent(window);

	// Initialize glad
	gladLoadGL();

	// specified the sizes of the area which I wish to effect (in this case all of it)
	glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// changing the color of the buffer to black with no transpernicy
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// swapping the front buffer with the front one
	glfwSwapBuffers(window);

	// waiting while the window is not closed
	while (!glfwWindowShouldClose(window)) {

		// refreshing the window so it won't be stuck
		glfwPollEvents();
	}

	// destroying the window
	glfwDestroyWindow(window);

	// terminating glfw
	glfwTerminate();
	return 0;
}