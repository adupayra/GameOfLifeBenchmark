#pragma once
#include <glad/glad.h>

class Shader
{	
private:
	GLuint id;

public:
	Shader(const GLchar*, const GLchar*);

	void use();
};

