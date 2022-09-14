#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

const GLint WIDTH = 1024, HEIGHT = 800;

int main()
{
	// GLFW Initialisation
	if(!glfwInit())
	{ 
		std::cerr << "GLFW Initialisation failed!" << std::endl;
		return 1;
	}

	// Setting GLFW window properties
	// OpenGL version - 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core profile - No Backward Comptability
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Enable Forward Comptability
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "mainWindow", NULL, NULL);

	if (!mainWindow)
	{
		std::cerr << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Make OpenGL Context the current context
	glfwMakeContextCurrent(mainWindow);

	// Allow modern openGL features
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW Initialisation failed!" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Main loop
	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow); // Double Buffering
	}

	glfwTerminate();
	return 0;
}