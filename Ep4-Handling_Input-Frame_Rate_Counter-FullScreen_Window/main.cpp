#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

const char* wTitle = "mainWindow";
const GLint WIDTH = 1024, HEIGHT = 800;
bool bFullScreen = false;

void closeWindow(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void showFrameRate(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // In seconds

	elapsedSeconds = currentSeconds - previousSeconds;

	// Update title 4 times per second
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double FPS = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / FPS; // In ms

		std::ostringstream outputStringStream;
		outputStringStream.precision(3);
		outputStringStream << std::fixed << wTitle << "  " << "FPS: " << FPS << "  Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outputStringStream.str().c_str());
			
		frameCount = 0;
	}
	frameCount++;
}

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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	// Core profile - No Backward Comptability
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Enable Forward Comptability
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	
	GLFWwindow* mainWindow = nullptr;

	if (bFullScreen)
	{
		GLFWmonitor* pPrimaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* pVideoMode = glfwGetVideoMode(pPrimaryMonitor);
		mainWindow = glfwCreateWindow(pVideoMode->width, pVideoMode->height, wTitle, pPrimaryMonitor, NULL);
	}
	else
	{
		mainWindow = glfwCreateWindow(WIDTH, HEIGHT, wTitle, NULL, NULL);
	}

	if (!mainWindow)
	{
		std::cerr << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Make OpenGL Context the current context
	glfwMakeContextCurrent(mainWindow);

	// Key Callback function
	glfwSetKeyCallback(mainWindow, closeWindow);

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
		showFrameRate(mainWindow);
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow); // Double Buffering
	}

	glfwTerminate();
	return 0;
}


