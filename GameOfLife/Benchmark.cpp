#include "Benchmark.h"
#include <iostream>

Benchmark::Benchmark(int seed)
{
	m_seed = seed;
	srand(seed);
}

void Benchmark::runBenchmark(std::string filename, int dimension, std::vector<ProcessMode> modes, int firstSize, int lastSize, bool gpuThreadsbm, int gpuThreads, int iterations, float timeout, int sizeStep) {
	std::vector<ProcessData> benchmarkData;

	if (!gpuThreadsbm)
	{
		for (int i = firstSize; i < lastSize; i += sizeStep) {
			std::cout << "Size: " << i << std::endl;

			for (ProcessMode mode : modes)
			{
				std::cout << ProcessData::convertToString(mode) << std::endl;
				GameManager instance(dimension, i, mode, true);
				ProcessData test = instance.runBench(iterations, timeout);
				benchmarkData.push_back(test);
				std::cout << "exec time: " << test.getExecMean() << std::endl;
				std::cout << "cpu usage: " << test.getCpuUsageMean() << std::endl;
				std::cout << "timeout " << test.getIsTimedout() << std::endl;
				std::cout << std::endl;
			}
		}
	}
	else
	{
		for (int j = firstSize; j < lastSize; j += sizeStep)
		{
			for (int i = 32; i < 1024; i = pow(i, 2)) {
				GameManager instance(dimension, j, GPU, true, i);
				benchmarkData.push_back(instance.runBench(iterations, timeout));

			}
		}
	}
}