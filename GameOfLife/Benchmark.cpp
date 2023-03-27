#include "Benchmark.h"
#include <iostream>

Benchmark::Benchmark(std::string filename, int seed)
{
	m_filename = filename;
	m_seed = seed;
	srand(seed);
}

void Benchmark::runBenchmark(int dimension, std::vector<ProcessMode> modes, int firstSize, int lastSize, bool gpuThreadsbm, int gpuThreads, int iterations, float timeout, int sizeStep) {
	m_benchmarkFile.open(m_filename);
	m_benchmarkFile << "Seed\n" << m_seed << "\nIterations;" << iterations << "\n\nWorld size\\Process method;";
	std::vector<ProcessData> benchmarkData;
	if (!gpuThreadsbm)
	{

		for (ProcessMode mode : modes) {
			m_benchmarkFile << ProcessData::convertToString(mode) << ";;;";
		}
		m_benchmarkFile << "\n";

		std::vector<int> skippedj;
		for (int i = firstSize; i < lastSize; i += sizeStep) {
			std::cout << "Size: " << i << std::endl;
			m_benchmarkFile << i << ";";
			for (int j = 0; j < modes.size(); j++)
			{
				if (std::find(skippedj.begin(), skippedj.end(), j) != skippedj.end()) {
					m_benchmarkFile << ";;;";
					continue;
				}
				std::cout << ProcessData::convertToString(modes[j]) << std::endl;
				GameManager instance(dimension, i, modes[j], true);
				ProcessData data = instance.runBench(iterations, timeout);
				benchmarkData.push_back(data);
				std::cout << "exec time: " << data.getExecMean() << std::endl;
				std::cout << "cpu usage: " << data.getCpuUsageMean() << std::endl;
				if (data.getExecMean() < timeout) {
					m_benchmarkFile << data.getExecMean() << ";" << data.getCpuUsageMean() << ";;";
				}
				else 
				{
					m_benchmarkFile << ";;;";
					skippedj.push_back(j);
				}
				std::cout << std::endl;
			}
			m_benchmarkFile << "\n";

		}
	}
	else
	{
		for (int j = 32; j <= 1024; j *= 2) {
			m_benchmarkFile << j << ";";
		}
		m_benchmarkFile << "\n";
		std::vector<int> skippedj;
		for (int i = firstSize; i < lastSize; i += sizeStep)
		{
			std::cout << "Size: " << i << std::endl;
			m_benchmarkFile << i << ";";
			for (int j = 32; j <= 1024; j *= 2)
			{
				std::cout << "Nb threads: " << j << std::endl;
				if (std::find(skippedj.begin(), skippedj.end(), j) != skippedj.end()) {
					m_benchmarkFile << ";";
					continue;
				}
				GameManager instance(dimension, i, GPU, true, j);
				ProcessData data = instance.runBench(iterations, timeout);
				benchmarkData.push_back(data);
				std::cout << "exec time: " << data.getExecMean() << std::endl;
				if (data.getExecMean() < timeout) {
					m_benchmarkFile << data.getExecMean() << ";";
				}
				else {
					m_benchmarkFile << ";";
					skippedj.push_back(j);
				}
				std::cout << std::endl;
			}
			m_benchmarkFile << "\n";
		}
	}
	m_benchmarkFile.close();
}

Benchmark::~Benchmark()
{
	if (m_benchmarkFile.is_open()) {
		m_benchmarkFile.close();
	}
}
