#include "GameManager.h"
#include "Benchmark.h"

int main(int argc, const char* argv) {
	bool benchmark = false;
	if (benchmark) {
		Benchmark bench("methodsBenchmark.csv");
		bench.runBenchmark(2, std::vector<ProcessMode>{	CPU,
			CPUAlt,
			CPUThreads,
			CPUppl,
			CPUThreadP,
			GPU}, 100, 3000, false, 256, 100, 500);
	}
	else {
		GameManager gameManager(2, 1000, GPU, false, 512);
		gameManager.run();
	}
}