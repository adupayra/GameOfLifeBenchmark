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
	WindowManager::width = width;
	WindowManager::height = height;

	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	WindowManager::wind = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!wind)
		exit(EXIT_FAILURE);
	glfwSetKeyCallback(wind, glfwKeyCallback);
	glfwSetFramebufferSizeCallback(wind, glfwFrameBuffersizeCallback);

	glfwMakeContextCurrent(wind);

	loadGlad();
	
}

WindowManager::~WindowManager()
{
	glfwDestroyWindow(wind);
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
	glfwSwapBuffers(wind);
}

void WindowManager::processEvents()
{
	glfwPollEvents();
}

void WindowManager::show()
{
	glfwShowWindow(wind);
}

bool WindowManager::getCloseState()
{
	return glfwWindowShouldClose(wind);
}

