#include "GraphicsDisplay.h"
#include <iostream>

void GLAPIENTRY GraphicsDisplay::openglMessageCallback(GLenum source,
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


void GraphicsDisplay::initViewport()
{
	glViewport(0, 0, windowManager->getWidth(), windowManager->getHeight());
	windowManager->show();
	glClearColor(0.5, 0.5, 0.5, 1.0);
}

GraphicsDisplay::GraphicsDisplay(int width, int height, int dimension, int cellsPerDim) {
	GraphicsDisplay::dimension = dimension;
	GraphicsDisplay::cellsPerDim = cellsPerDim;
	GraphicsDisplay::nbCells = pow(cellsPerDim, dimension);

	GraphicsDisplay::windowManager = new WindowManager{ width, height, "2D Game of life" };

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglMessageCallback, 0);

	initViewport();
	GraphicsDisplay::shaderManager = NULL;
}

void GraphicsDisplay::render(const uint8_t* cells)
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw(cells);

	windowManager->update();
	windowManager->processEvents();
}


GraphicsDisplay::~GraphicsDisplay()
{
	delete windowManager;
	if(shaderManager != NULL)
		delete shaderManager;
}

