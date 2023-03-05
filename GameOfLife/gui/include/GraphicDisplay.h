#pragma once
#include <vector>

class GraphicDisplay
{
protected:
	int dimension;
	int cellsPerDim;
public:
	GraphicDisplay(int, int);
	virtual void update(std::vector<bool>);
	~GraphicDisplay();
};

