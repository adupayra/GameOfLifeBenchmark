#include "GameManager.h"
#include "ClassicRules.h"
#include "Graphics2D.h"
#include <chrono>
#include <iostream>
#include <stdlib.h>

GameManager::GameManager(int dimension, int cellsPerDim) {
	srand(31231);

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
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	int i = 1;
	while (!graphicsDisplay->windowManager->isClosedState()) {
		std::cout << "Iteration " << i << std::endl;

		auto t1 = high_resolution_clock::now();
		gameInstance->step();
		auto t2 = high_resolution_clock::now();

		duration<double, std::milli> ms_double = t2 - t1;
		std::cout << "Cells update time: " << ms_double.count() << "ms\n";
		system("CLS");

		graphicsDisplay->render(gameInstance->cells);
		i++;
	}
}