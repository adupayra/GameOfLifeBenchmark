#include "GameManager.h"
#include "Benchmark.h"

int main(int argc, const char* argv) {
	bool benchmark = false;
	if (benchmark) {
		Benchmark bench("test3.csv");
		bench.runBenchmark(2, std::vector<ProcessMode>{CPUAlt, CPUThreads}, 1000, 5000);
	}
	else {
		GameManager gameManager(2, 6000, CPUAlt);
		gameManager.run();
	}
}