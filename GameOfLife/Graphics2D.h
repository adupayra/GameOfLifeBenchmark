#pragma once
#include "GraphicsDisplay.h"

class Graphics2D: GraphicsDisplay
{
private:

	void draw(uint8_t*);

	float vertices[12] = {
		-1.0f, 1.0f, 0.0f, 
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	float indices[6] = {
		0, 1, 2, 0, 2, 3
	};

	GLuint VBO;
	GLuint VAO;
	GLuint textureID;	
	
	Graphics2D(int width, int height, int dimension, int cellsPerDim);

	void generateTexture(uint8_t* cells);



};

