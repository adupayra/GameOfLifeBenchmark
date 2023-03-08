#pragma once
#include <WindowManager.h>
#include <Shader.h>
#include <vector>

class GraphicsDisplay
{
private:
	void initViewport();

protected:
	int m_dimension;
	int m_cellsPerDim;
	int m_nbCells;
	virtual void draw(const uint8_t*) = 0;
	Shader* m_shaderManager;


public:

	WindowManager* m_windowManager;

	GraphicsDisplay(int, int, int, int);
	void render(const uint8_t*);

	~GraphicsDisplay();

	static void GLAPIENTRY openglMessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
};

