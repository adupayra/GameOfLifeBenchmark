#include "GameManager.h"
#include "ClassicRules.h"
#include "TextDisplay.h"
#include "GraphicDisplay.h"

GameManager::GameManager(int dimensions, int cellsPerDim) {
	if (dimensions != 3 && dimensions != 2) {
		throw "Dimensions different than 2 and 3 are not handled";
	}
	GameManager::gameInstance = new Game(dimensions, cellsPerDim, new ClassicRules(dimensions, cellsPerDim));
	//GameManager::gameView = new TextDisplay(cellsPerDim);
	GameManager::gameView = new GraphicDisplay(dimensions, cellsPerDim);

	gameInstance->initGrid();

}

GameManager::~GameManager() {
	delete gameInstance;
	delete gameView;
}

void GameManager::run() {
	while (true) {
		gameInstance->step();

	}
}