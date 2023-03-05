#include "GameManager.h"
#include "ClassicRules.h"
#include "GraphicsDisplay.h"

GameManager::GameManager(int dimensions, int cellsPerDim) {
	if (dimensions != 3 && dimensions != 2) {
		throw "Dimensions different than 2 and 3 are not handled";
	}
	GameManager::gameInstance = new Game(dimensions, cellsPerDim, new ClassicRules(dimensions, cellsPerDim));
	GameManager::graphicsDisplay = new GraphicsDisplay(512, 512, dimensions, cellsPerDim);

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
		graphicsDisplay->update(gameInstance->cells);
	}
}