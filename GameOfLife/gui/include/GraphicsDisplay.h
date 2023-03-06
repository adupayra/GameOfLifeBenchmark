#pragma once
#include <WindowManager.h>
#include <Shader.h>
#include <vector>

class GraphicsDisplay
{
private:
	void initViewport();

protected:
	int dimension;
	int cellsPerDim;
	int nbCells;
	virtual void draw(const uint8_t*) = 0;
	Shader* shaderManager;


public:

	WindowManager* windowManager;

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

