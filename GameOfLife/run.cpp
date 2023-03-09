#include "GameManager.h"

int main(int argc, const char* argv) {
	srand(31231);
	GameManager gameManager(2, 4096, CPUThreadP);
	gameManager.run();
	
}