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
	virtual void draw(uint8_t*) = 0;
	virtual void initShaderManager() = 0;
	Shader* shaderManager;


public:

	WindowManager* windowManager;

	GraphicsDisplay(int, int, int, int);
	void update(uint8_t*);

	~GraphicsDisplay();

	static void GLAPIENTRY openglMessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
};

