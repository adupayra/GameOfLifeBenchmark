#pragma once
#include <WindowManager.h>
#include <Shader.h>
#include <vector>

class GraphicsDisplay
{
private:
	void initViewport();
	Shader shaderManager;
	void update(std::vector<bool>);

protected:
	int dimension;
	int cellsPerDim;
	virtual void draw(std::vector<int>);
public:
	WindowManager windowManager;

	GraphicsDisplay(int, int, int, int);
	~GraphicsDisplay();

	static void GLAPIENTRY openglMessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
};

