#pragma once

#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window(); // default constructor
	Window(const char* windowTitle, int windowWidth, int windowHeight, bool fullScreenWindow); // explicit constructor (parameterized)
	bool init();
	bool getWindowCloseFlag() { return glfwWindowShouldClose(mainWindow); }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	void monitorFrameRate();

	~Window();
private:
	const char* m_WindowTitle;
	int m_Width, m_Height;
	bool m_bFullScreen;
	GLFWwindow* mainWindow;
};

