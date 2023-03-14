#include "GameManager.h"
#include "Benchmark.h"

int main(int argc, const char* argv) {
	bool benchmark = true;
	if (benchmark) {
		Benchmark bench("test4.csv");
		bench.runBenchmark(2, std::vector<ProcessMode>{CPUAlt, CPUThreads}, 100, 200, false, 256, 20, 500);
	}
	else {
		GameManager gameManager(2, 25000, GPU, false, 512);
		gameManager.run();
	}
}