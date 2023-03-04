#pragma once
#include "GameView.h"

class TextDisplay: public GameView
{
private:
	char* gridBuffer;
public:
	TextDisplay(int);

	void update(std::vector<bool>) override;

	~TextDisplay();

	void initView() override;
};

