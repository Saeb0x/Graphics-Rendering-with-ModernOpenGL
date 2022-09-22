#include "Window.h"

Window::Window()
{
	m_WindowTitle = "mainWindow";
	m_Width = 800;
	m_Height = 600;
	m_bFullScreen = false;
	mainWindow = nullptr;
}

Window::Window(const char* windowTitle, int windowWidth, int windowHeight, bool fullScreenWindow)
{
	m_WindowTitle = windowTitle;
	m_Width = windowWidth;
	m_Height = windowHeight;
	m_bFullScreen = fullScreenWindow;
	mainWindow = nullptr;
}

bool Window::init()
{
	// GLFW Initialisation
	if (!glfwInit())
	{
		std::cerr << "GLFW Initialisation failed!" << std::endl;
		return false;
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


	if (m_bFullScreen)
	{
		GLFWmonitor* pPrimaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* pVideoMode = glfwGetVideoMode(pPrimaryMonitor);
		mainWindow = glfwCreateWindow(pVideoMode->width, pVideoMode->height, m_WindowTitle, pPrimaryMonitor, NULL);
	}
	else
	{
		mainWindow = glfwCreateWindow(m_Width, m_Height, m_WindowTitle, NULL, NULL);
	}

	if (!mainWindow)
	{
		std::cerr << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		return false;
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
		return false;
	}

	return true;
}

void Window::monitorFrameRate()
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
		outputStringStream << std::fixed << m_WindowTitle << "  " << "FPS: " << FPS << "  Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(mainWindow, outputStringStream.str().c_str());

		frameCount = 0;
	}
	frameCount++;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
}