#include "Benchmark.h"
#include <iostream>

Benchmark::Benchmark(int dimension, std::vector<ProcessMode> modes, int firstSize, int lastSize, bool gpuThreadsbm, int gpuThreads, int iterations, float timeout, int sizeStep, int seed)
{
	m_seed = seed;
	srand(seed);
	if (!gpuThreadsbm)
	{
		//std::vector<std::pair<ProcessMode, double>> times;
		for (int i = firstSize; i < lastSize; i += sizeStep) {
			std::cout << "Size: " << i << std::endl;
			for (ProcessMode mode : modes)
			{
				GameManager instance(dimension, i, mode, true);
				instance.runBench(iterations, timeout);
				//times.push_back(std::pair<ProcessMode, double>(mode, instance.getMeantime()));
				std::cout << mode << ": " << instance.getMeantime() << std::endl;
			}
		}
	}
	else
	{
		for (int j = firstSize; j < lastSize; j += sizeStep)
		{
			for (int i = 32; i < 1024; i = pow(i, 2)) {
				GameManager instance(dimension, j, GPU, true, i);
			}
		}
	}

}
