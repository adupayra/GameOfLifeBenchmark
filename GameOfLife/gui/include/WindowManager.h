#pragma once
#include <glad/glad.h>
#include <glfw3.h>

class WindowManager
{
private:
	GLFWwindow* wind;
	int width;
	int height;

	void loadGlad();
public:
	WindowManager(int, int, const char*);

	~WindowManager();

	GLFWwindow* getWindow() { return wind; }

	int getWidth() { return width; }

	int getHeight() { return height; }

	static void glfwErrorCallback(int, const char*);

	static void glfwKeyCallback(GLFWwindow*, int, int, int, int);

	static void glfwFrameBuffersizeCallback(GLFWwindow*, int, int);

	void update();

	void processEvents();

	void show();

	bool getCloseState();

};

