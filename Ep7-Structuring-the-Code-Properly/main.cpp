#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

Window mainWindow;
Mesh* pTriangle = new Mesh();
Shader* pShaderProg = new Shader();

// Vertex Shader
const GLchar* vertexShader = "Shaders/shader.vertex";

// Fragment Shader
const GLchar* fragmentShader = "Shaders/shader.fragment";

int main()
{
	mainWindow = Window("mainWindow", 1024, 800, false);

	if (!mainWindow.init())
	{
		std::cerr << "Error while initializing the window!!" << std::endl;
		return 1;
	}

	GLfloat vertices[] =
	{
		0.0f, 1.0f, 0.0f, // Top vertex
		1.0f, -1.0f, 0.0f, // Right-Bottom vertex
		-1.0f,-1.0f,0.0f // Left-Bottom vertex
	};

	pTriangle->createMesh(vertices, 3);
	
	pShaderProg->createShaderFromFiles(vertexShader, fragmentShader);

	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

	// Main loop
	while (!mainWindow.getWindowCloseFlag())
	{
		mainWindow.monitorFrameRate();
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		pShaderProg->useShader();
		pTriangle->renderMesh();
		glBindVertexArray(0);
		glUseProgram(0);

		mainWindow.swapBuffers(); // Double Buffering
	}
	
	// De-allocation
	delete pTriangle, pShaderProg;
	pTriangle = nullptr;
	pShaderProg = nullptr;

	glfwTerminate();
	return 0;
}

