#include "GameManager.h"
#include "Benchmark.h"

int main(int argc, const char* argv) {
	bool benchmark = true;
	if (benchmark) {
		Benchmark bench("test2.csv");
		bench.runBenchmark(2, std::vector<ProcessMode>{CPU, CPUAlt, CPUppl, CPUThreads, CPUThreadP, GPU}, 200, 5000, true);
	}
	else {
		GameManager gameManager(2, 200, GPU);
		gameManager.run();
	}

}