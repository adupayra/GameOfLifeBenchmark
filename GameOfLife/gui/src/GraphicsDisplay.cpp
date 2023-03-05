#include "GraphicsDisplay.h"
#include <iostream>

void GraphicsDisplay::initViewport()
{
	glViewport(0, 0, windowManager.getWidth(), windowManager.getHeight());
	windowManager.show();
	glClearColor(0.5, 0.5, 0.5, 1.0);
}

GraphicsDisplay::GraphicsDisplay(int width, int height, int dimension, int cellsPerDim) {
	GraphicsDisplay::dimension = dimension;
	GraphicsDisplay::cellsPerDim = cellsPerDim;

	GraphicsDisplay::windowManager = WindowManager{ width, height, "2D Game of life" };
	
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglMessageCallback, 0);

	initViewport();
	shaderManager.use();
}

void GraphicsDisplay::update(std::vector<bool>)
{
	while (!windowManager.isClosedState()) {

	}
}

GraphicsDisplay::~GraphicsDisplay()
{

}

void GraphicsDisplay::draw(std::vector<int> test) {

}

void GLAPIENTRY openglMessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") << " type = "
		<< type << " severity = " << severity << " message = " << message << std::endl;
}
