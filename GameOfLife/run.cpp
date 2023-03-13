#include "GameManager.h"
#include "Benchmark.h"

int main(int argc, const char* argv) {
	bool benchmark = true;
	if (benchmark) {
		Benchmark bench;
		bench.runBenchmark(2, std::vector<ProcessMode>{CPU, CPUAlt, CPUThreads, CPUThreadP, GPU}, 200, 5000);
	}
	else {
		GameManager gameManager(2, 200, GPU);
		gameManager.run();
	}

}