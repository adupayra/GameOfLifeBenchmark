#pragma once
#include <glad/glad.h>

class Shader
{	
private:
	GLuint id;

	const GLchar* vs =
		"#version 460 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aCol;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec2 texCoords;\n"
		"out vec3 ourCol;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	ourCol = aCol;\n"
		"	texCoords = aTexCoord;\n"
		"}\0";

	const GLchar* fs =
		"#version 460 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourCol;\n"
		"in vec2 texCoords;\n"
		"uniform sampler2D sampleTexture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(sampleTexture, texCoords);\n"
		"}\0";

public:
	Shader();

	void use();
};

