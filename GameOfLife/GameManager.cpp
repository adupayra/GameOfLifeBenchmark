#include "GameManager.h"
#include "ClassicRules.h"
#include "Graphics2D.h"

GameManager::GameManager(int dimension, int cellsPerDim) {
	if (dimension != 3 && dimension != 2) {
		throw "Dimensions different than 2 and 3 are not handled";
	}
	GameManager::gameInstance = new Game(dimension, cellsPerDim, new ClassicRules(dimension, cellsPerDim));

	if(dimension == 2)
		GameManager::graphicsDisplay = new Graphics2D(600, 512, dimension, cellsPerDim);

	gameInstance->initGrid();

	run();
}

GameManager::~GameManager() {
	delete gameInstance;
	delete graphicsDisplay;
}

void GameManager::run() {
	while (!graphicsDisplay->windowManager->isClosedState()) {
		gameInstance->step();
		graphicsDisplay->render(gameInstance->cells);
	}
}