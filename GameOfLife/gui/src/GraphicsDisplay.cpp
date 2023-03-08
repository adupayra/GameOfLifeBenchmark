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
	glViewport(0, 0, m_windowManager->getWidth(), m_windowManager->getHeight());
	m_windowManager->show();
	glClearColor(0.5, 0.5, 0.5, 1.0);
}

GraphicsDisplay::GraphicsDisplay(int width, int height, int dimension, int cellsPerDim) {
	GraphicsDisplay::m_dimension = dimension;
	GraphicsDisplay::m_cellsPerDim = cellsPerDim;
	GraphicsDisplay::m_nbCells = pow(cellsPerDim, dimension);

	GraphicsDisplay::m_windowManager = new WindowManager{ width, height, "2D Game of life" };

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglMessageCallback, 0);

	initViewport();
	GraphicsDisplay::m_shaderManager = NULL;
}

void GraphicsDisplay::render(const uint8_t* cells)
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw(cells);

	m_windowManager->update();
	m_windowManager->processEvents();
}


GraphicsDisplay::~GraphicsDisplay()
{
	delete m_windowManager;
	if(m_shaderManager != NULL)
		delete m_shaderManager;
}

