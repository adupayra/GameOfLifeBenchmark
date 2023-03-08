#include "Graphics2D.h"
#include <iostream>


void Graphics2D::draw(const uint8_t* cells)
{
	generateTexture(cells);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Graphics2D::Graphics2D(int width, int height, int dimension, int cellsPerDim) : GraphicsDisplay(width, height, dimension, cellsPerDim)
{

	int textureSize = m_nbCells * 3;
	m_textureData = new uint8_t[textureSize];
	Graphics2D::m_shaderManager = new Shader(m_vs, m_fs);
	Graphics2D::m_shaderManager->use();

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, NULL, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, NULL, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices, GL_STATIC_DRAW);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



}

void Graphics2D::generateTexture(const uint8_t* cells)
{
	uint8_t value = 0;
	int j = 0;
	for (int i = 0; i < m_nbCells; ++i) {
		value = cells[i] * 255;
		m_textureData[j] = value;
		m_textureData[j + 1] = value;
		m_textureData[j + 2] = value;
		j += 3;

	}


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  m_cellsPerDim, m_cellsPerDim, 0, GL_RGB, GL_UNSIGNED_BYTE, m_textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
}
