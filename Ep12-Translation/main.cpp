#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

bool inverseDirection = false;
float yOffset = 0.0f;
const float yIncrement = 0.01f;
float yOffsetMaximum = 0.6f;

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

		if (!inverseDirection)
		{
			yOffset += yIncrement;
		}
		else {
			yOffset -= yIncrement;
		}

		if (abs(yOffset) >= yOffsetMaximum)
		{
			inverseDirection = !inverseDirection;
		}

		
		glm::mat4 model(1.0f); // Identity Matrix
		model = glm::rotate(model, 90.0f * 3.14f / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(yOffset, yOffset, 0.0f));
		


		glUniformMatrix4fv(pShaderProg->uniformModel, 1, false, glm::value_ptr(model));

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

