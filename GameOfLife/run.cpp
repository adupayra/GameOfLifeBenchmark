#include "GameManager.h"

int main(int argc, const char* argv) {
	srand(31231);
	GameManager gameManager(2, 512, CPU);
	gameManager.run();
}