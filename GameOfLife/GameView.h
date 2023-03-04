#pragma once
#include <vector>

class GameView
{
protected:
	int dimension;
	int cellsPerDim;
public:
	virtual void update(std::vector<bool>) = 0;
	virtual void initView() = 0;
};

