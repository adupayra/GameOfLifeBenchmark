#include "ClassicRules2D.h"


bool ClassicRules2D::isAlive(uint8_t cell, int nbNeighbours)
{
	if (cell) {
		return nbNeighbours == 2 || nbNeighbours == 3;
	}
	return nbNeighbours == 3;
}
