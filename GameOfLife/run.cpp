#include "GameManager.h"
#include "Benchmark.h"

int main(int argc, const char* argv) {
	//srand(31231);
	//GameManager gameManager(2, 512, CPU, true);

	Benchmark(2, std::vector<ProcessMode>{CPU, CPUAlt, CPUThreads, CPUThreadP, GPU}, 200, 5000, false);

	//gameManager.run();
}