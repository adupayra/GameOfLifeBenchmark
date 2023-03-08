#include "Shader.h"
#include <stdio.h>


Shader::Shader(const GLchar* vsSource, const GLchar* fsSource)
{
	GLuint vsId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsId, 1, &vsSource, NULL);
	glCompileShader(vsId);

	GLuint fsId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsId, 1, &fsSource, NULL);
	glCompileShader(fsId);

	m_id = glCreateProgram();
	glAttachShader(m_id, vsId);
	glAttachShader(m_id, fsId);

	glDeleteShader(vsId);
	glDeleteShader(fsId);

	glLinkProgram(m_id);
}

void Shader::use() {
	glUseProgram(m_id);
}
