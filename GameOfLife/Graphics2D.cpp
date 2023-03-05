#include "Graphics2D.h"



void Graphics2D::draw(uint8_t*)
{
}

Graphics2D::Graphics2D(int width, int height, int dimension, int cellsPerDim) : GraphicsDisplay(width, height, dimension, cellsPerDim)
{
	Graphics2D::shaderManager = new Shader(vs, fs);
	Graphics2D::shaderManager->use();
}

void Graphics2D::generateTexture(uint8_t* cells)
{
}
