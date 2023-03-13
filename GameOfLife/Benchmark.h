#pragma once
#include "GameManager.h"

class Benchmark
{
private:
	std::vector<ProcessMode> m_benchmarkedmodes;
	int m_seed;

public:
	Benchmark(int seed = 31231);
	void runBenchmark(std::string filename, int dimension, std::vector<ProcessMode> modes, int firstSize, int lastSize, bool gpuThreadsbm = false, int gpuThreads = 256, int iterations = 500, float timeout = 100, int sizeStep = 500);
	
};

