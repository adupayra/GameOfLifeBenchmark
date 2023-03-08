#pragma once
#include <glad/glad.h>

class Shader
{	
private:
	GLuint m_id;

public:
	Shader(const GLchar*, const GLchar*);

	void use();
};

