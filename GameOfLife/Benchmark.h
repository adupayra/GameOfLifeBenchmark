#pragma once
#include "GameManager.h"
#include <fstream>

class Benchmark
{
private:
	std::vector<ProcessMode> m_benchmarkedmodes;
	int m_seed;
	std::string m_filename;
	std::ofstream m_benchmarkFile;

public:
	Benchmark(std::string filename, int seed = 31231);
	void runBenchmark(int dimension, std::vector<ProcessMode> modes, int firstSize, int lastSize, bool gpuThreadsbm = false, int gpuThreads = 256, int iterations = 500, float timeout = 100, int sizeStep = 500);
	~Benchmark();
};

