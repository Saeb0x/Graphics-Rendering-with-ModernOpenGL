#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

const char* wTitle = "mainWindow";
const GLint WIDTH = 1024, HEIGHT = 800;
bool bFullScreen = false;

void closeWindow(GLFWwindow* window, int key, int scancode, int action, int mods);
void showFrameRate(GLFWwindow* window);

GLuint VAO, VBO, shaderProg;
GLuint VS, FS;


// Vertex Shader
const GLchar* vertexShader =
"#version 330\n"
"layout (location = 0) in vec3 position;"
"void main()"
"{"
"	gl_Position = vec4(0.5*position.x, 0.5*position.y, position.z, 1.0f);"
"}";

// Fragment Shader
const GLchar* fragmentShader = 
"#version 330\n"
"out vec4 fragmentColor;"
"void main()"
"{"
"	fragmentColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
"}";

void createTriangle()
{
	GLfloat vertices[] =
	{
		0.0f, 1.0f, 0.0f, // Top vertex
		1.0f, -1.0f, 0.0f, // Right-Bottom vertex
		-1.0f,-1.0f,0.0f // Left-Bottom vertex
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void createShaders()
{
	VS = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VS, 1, &vertexShader, NULL);

	FS = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FS, 1, &fragmentShader, NULL);
}

void compileShaders()
{
	GLint result;
	GLchar infoLog[1024];

	glCompileShader(VS);
	glGetShaderiv(VS, GL_COMPILE_STATUS, &result);
	
	if (!result)
	{
		glGetShaderInfoLog(VS, sizeof(infoLog), NULL, infoLog);
		std::cerr << "Failure in compiling the vertex shader: " << infoLog << std::endl;
		return;
	}

	glCompileShader(FS);
	glGetShaderiv(FS, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(FS, sizeof(infoLog), NULL, infoLog);
		std::cerr << "Failure in compiling the fragment shader: " << infoLog << std::endl;
		return;
	}
}

void createShaderProg()
{
	shaderProg = glCreateProgram();
	
	glAttachShader(shaderProg, VS);
	glAttachShader(shaderProg, FS);

	glLinkProgram(shaderProg);
}

int main()
{
	// GLFW Initialisation
	if (!glfwInit())
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


	createTriangle();
	createShaders();
	compileShaders();
	createShaderProg();

	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	
	// Main loop
	while (!glfwWindowShouldClose(mainWindow))
	{
		showFrameRate(mainWindow);
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProg);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		
		glfwSwapBuffers(mainWindow); // Double Buffering
	}
	glDeleteProgram(shaderProg);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

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

