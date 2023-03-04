#pragma once
#include "GameView.h"
class GraphicDisplay :
    public GameView
{
public:
	GraphicDisplay();

	void update(std::vector<bool>) override;

	~GraphicDisplay();

	void initView() override;

	int test();
};

