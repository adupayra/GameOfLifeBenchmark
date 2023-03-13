#include "Benchmark.h"
#include <iostream>

Benchmark::Benchmark(int dimension, std::vector<ProcessMode> modes, int firstSize, int lastSize, bool gpuThreadsbm, int gpuThreads, int iterations, float timeout, int sizeStep, int seed)
{
	m_seed = seed;
	srand(seed);
	if (!gpuThreadsbm)
	{
		//std::vector<std::pair<ProcessMode, double>> times;
		std::vector<std::pair<int, std::vector<std::pair<ProcessMode, std::vector<double>>>>> benchmarkData;
		for (int i = firstSize; i < lastSize; i += sizeStep) {
			std::cout << "Size: " << i << std::endl;
			double meanTime = 0;
			std::vector<std::pair<ProcessMode, std::vector<double>>> valuesComparison;

			for (ProcessMode mode : modes)
			{
				std::pair<ProcessMode, std::vector<double>> instanceValues;
				std::vector<double> values;
				GameManager instance(dimension, i, mode, true);
				bool isTimedout = instance.runBench(iterations, timeout);
				if (isTimedout) {
					values.push_back(-1);

				}
				else {
					values.push_back(instance.getMeantime());
						
				}

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
