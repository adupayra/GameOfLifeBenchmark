#include "Graphics2D.h"
#include <iostream>


void Graphics2D::draw(uint8_t* cells)
{
	generateTexture(cells);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Graphics2D::Graphics2D(int width, int height, int dimension, int cellsPerDim) : GraphicsDisplay(width, height, dimension, cellsPerDim)
{

	int textureSize = nbCells * 3;
	textureData = new uint8_t[textureSize];
	Graphics2D::shaderManager = new Shader(vs, fs);
	Graphics2D::shaderManager->use();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexArrayAttrib(VAO, 0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);



}

void Graphics2D::generateTexture(uint8_t* cells)
{
	uint8_t value = 0;
	//int j = 0;
	//for (int i = 0; i < nbCells; ++i) {
	//	//value = cells[i] * 255;
	//	//textureData[j] = value;
	//	//textureData[j + 1] = value;
	//	//textureData[j + 2] = value;

	//	if (j < nbCells * 3 / 2)
	//	{
	//		textureData[j] = 0;
	//		textureData[j + 1] = 0;
	//		textureData[j + 2] = 0;
	//	}
	//	else {
	//		textureData[j] = 255;
	//		textureData[j + 1] = 255;
	//		textureData[j + 2] = 255;
	//	}
	//	j += 3;

	//}

	for (int i = 0; i < nbCells * 3; i += 3) {
		if (i < nbCells * 3 / 2)
		{
			textureData[i] = 0;
			textureData[i + 1] = 0;
			textureData[i + 2] = 0;
		}
		else {
			textureData[i] = 255;
			textureData[i + 1] = 255;
			textureData[i + 2] = 255;
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  cellsPerDim, cellsPerDim, 0, GL_RGB, GL_UNSIGNED_INT, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
}
