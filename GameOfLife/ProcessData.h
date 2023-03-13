#pragma once
#include "ProcessEnum.h"
#include <windows.h>
#include <stdint.h>
#include <chrono>
#include <vector>

class ProcessData
{
private:
	ProcessMode m_mode;

	bool m_isTimedout = false;

    ULONGLONG uOldIdle = 0;
    ULONGLONG uOldKrnl = 0;
    ULONGLONG uOldUsr = 0;

    ULONGLONG convertFiletime(const FILETIME& filetime);

    void startMeasuringCPU();

    void computeCPUUsage();

    std::chrono::steady_clock::time_point m_oldTime;

    std::vector<int> m_cpuUsages;

    std::vector<double> m_execTimes;

    double m_cpuUsageMean = 0;

    double m_execMean = 0;
public:

    void computeMeans();

    double getCpuUsageMean() {
        return m_cpuUsageMean;
    }

    double getExecMean() {
        return m_execMean;
    }

    double getExecTime() {
        return m_execTimes.back();
    }

    int getCpuUsage() {
        return m_cpuUsages.back();
    }
	ProcessData(ProcessMode mode);

    void startMeasurements();

    void endMeasurements();




};

