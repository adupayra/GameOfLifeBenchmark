#pragma once
#include "GraphicsDisplay.h"

class Graphics2D: public GraphicsDisplay
{
public:
	Graphics2D(int width, int height, int dimension, int cellsPerDim);
private:
	const GLchar* m_vs =
		"#version 460 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec2 aTexCoord;\n"
		"out vec2 texCoords;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	texCoords = aTexCoord;\n"
		"}\0";

	const GLchar* m_fs =
		"#version 460 core\n"
		"out vec4 FragColor;\n"
		"in vec2 texCoords;\n"
		"uniform sampler2D sampleTexture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(sampleTexture, texCoords);\n"
		"}\0";

	void draw(const uint8_t*);


	float m_vertices[20] = {
		 1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 
		 1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 
		-1.0f, -1.0f, 0.0f,    0.0f, 0.0f,  
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f    
	};


	unsigned int m_indices[6] = {
	0, 1, 2, 0, 2, 3
	};



	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_textureID;	
	
	uint8_t* m_textureData;
	void generateTexture(const uint8_t* cells);



};

