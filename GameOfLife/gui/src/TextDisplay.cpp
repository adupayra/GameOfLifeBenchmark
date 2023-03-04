#include "TextDisplay.h"
#include "iostream"

void TextDisplay::update(std::vector<bool> cellsToChange) {

}

TextDisplay::TextDisplay(int cellsPerDim) {
	TextDisplay::dimension = 2;
	TextDisplay::cellsPerDim = cellsPerDim;
	TextDisplay::gridBuffer = new char(2 * cellsPerDim);

}

void TextDisplay::initView() {
	for (int i = 0; i < cellsPerDim * 2; i++) {
		gridBuffer[i] = '0';
	}
}

TextDisplay::~TextDisplay() {
	delete gridBuffer;
}