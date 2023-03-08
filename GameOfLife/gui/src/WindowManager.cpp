#include "WindowManager.h"
#include <iostream>

void WindowManager::loadGlad()
{
	if (!gladLoadGL()) {
		std::cerr << "Glad failed to load" << std::endl;
		exit(EXIT_FAILURE);
	}
}

WindowManager::WindowManager(int width, int height, const char* title)
{
	WindowManager::m_width = width;
	WindowManager::m_height = height;

	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	WindowManager::m_wind = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!m_wind)
		exit(EXIT_FAILURE);
	glfwSetKeyCallback(m_wind, glfwKeyCallback);
	glfwSetFramebufferSizeCallback(m_wind, glfwFrameBuffersizeCallback);

	glfwMakeContextCurrent(m_wind);

	loadGlad();
	
}

WindowManager::~WindowManager()
{
	glfwDestroyWindow(m_wind);
	glfwTerminate();
}

void WindowManager::glfwErrorCallback(int error, const char* desc)
{
	std::cerr << "GLFW Error " << desc << " with code " << error << std::endl;
}

void WindowManager::glfwKeyCallback(GLFWwindow* wind, int key, int scancode, int action, int mods)
{
}

void WindowManager::glfwFrameBuffersizeCallback(GLFWwindow* wind, int width, int height)
{
	glViewport(0, 0, width, height);
}

void WindowManager::update()
{
	glfwSwapBuffers(m_wind);
}

void WindowManager::processEvents()
{
	glfwPollEvents();
}

void WindowManager::show()
{
	glfwShowWindow(m_wind);
}

bool WindowManager::isClosedState()
{
	return glfwWindowShouldClose(m_wind);
}

