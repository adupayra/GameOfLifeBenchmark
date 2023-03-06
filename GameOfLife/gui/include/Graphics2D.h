#pragma once
#include "GraphicsDisplay.h"

class Graphics2D: public GraphicsDisplay
{
public:
	Graphics2D(int width, int height, int dimension, int cellsPerDim);
private:
	const GLchar* vs =
		"#version 460 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"out vec2 texCoords;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	texCoords = aPos.xy;\n"
		"}\0";

	const GLchar* fs =
		"#version 460 core\n"
		"out vec4 FragColor;\n"
		"in vec2 texCoords;\n"
		"uniform sampler2D sampleTexture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(sampleTexture, texCoords);\n"
		"}\0";

	void draw(uint8_t*);

	float vertices[12] = {
	-1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f
	};

	unsigned int indices[6] = {
		0, 1, 3, 0, 3, 2
	};

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	GLuint textureID;	
	
	uint8_t* textureData;
	void generateTexture(uint8_t* cells);



};

