#include "ProcessData.h"
#include <iostream>

ProcessData::ProcessData(ProcessMode mode) {
	m_mode = mode;
}

void ProcessData::printLastErrorString(DWORD errorMessage)
{
    LPSTR messageBuffer = nullptr;

    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessage, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    std::string message(messageBuffer, size);
    
    LocalFree(messageBuffer);

    std::cerr << message << std::endl;        
}


ULONGLONG ProcessData::convertFiletime(const FILETIME& filetime) {
    return ((ULONGLONG)filetime.dwHighDateTime << 32) | filetime.dwLowDateTime;

}

void ProcessData::startMeasuringCPU() {
    FILETIME ftIdle, ftKrnl, ftUsr;

    if (!GetSystemTimes(&ftIdle, &ftKrnl, &ftUsr)) {
        printLastErrorString(GetLastError());
        exit(EXIT_FAILURE);
    }
    uOldIdle = convertFiletime(ftIdle);
    uOldKrnl = convertFiletime(ftKrnl);
    uOldUsr = convertFiletime(ftUsr);
}

void ProcessData::computeCPUUsage()
{
    if (uOldIdle == 0 && uOldKrnl == 0 && uOldUsr == 0)
        return;

    int nRes = 0;

    FILETIME ftIdle, ftKrnl, ftUsr;
    if (!GetSystemTimes(&ftIdle, &ftKrnl, &ftUsr))
    {
        printLastErrorString(GetLastError());
        exit(EXIT_FAILURE);
    }
    ULONGLONG uIdle = convertFiletime(ftIdle);
    ULONGLONG uKrnl = convertFiletime(ftKrnl);
    ULONGLONG uUsr = convertFiletime(ftUsr);

    ULONGLONG uDiffIdle = uIdle - uOldIdle;
    ULONGLONG uDiffKrnl = uKrnl - uOldKrnl;
    ULONGLONG uDiffUsr = uUsr - uOldUsr;

    if (uDiffKrnl + uDiffUsr)
    {
        //Calculate percentage
        nRes = (int)((uDiffKrnl + uDiffUsr - uDiffIdle) * 100 / (uDiffKrnl + uDiffUsr));

        //Check value and correct it (Just in case)
        if (nRes < 0)
            nRes = 0;
        else if (nRes > 100)
            nRes = 100;
    }

    uOldIdle = uIdle;
    uOldKrnl = uKrnl;
    uOldUsr = uUsr;

    m_cpuUsages.push_back(nRes);

}

void ProcessData::startMeasurements() {
    m_oldTime = std::chrono::high_resolution_clock::now();
    startMeasuringCPU();
}

void ProcessData::endMeasurements() {
    computeCPUUsage();
    std::chrono::steady_clock::time_point newTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> msDouble = newTime - m_oldTime;
    m_execTimes.push_back(msDouble.count());
}

void ProcessData::computeMeans() {
    double sumTimes = 0;
    for (int i = 0; i < m_execTimes.size(); i++) {
        sumTimes += m_execTimes[i];
    }
    m_execMean = sumTimes / m_execTimes.size();

    int sumCpu = 0;
    for (int i = 0; i < m_cpuUsages.size(); i++) {
        sumCpu += m_cpuUsages[i];
    }
    m_cpuUsageMean = sumCpu / m_cpuUsages.size();
}

std::string ProcessData::convertToString(ProcessMode mode) {
    switch (mode) {
    case CPU:
        return "CPU";
        break;
    case CPUAlt: return "CPUALT";
        break;
    case CPUThreads: return "CPU Threads";
        break;
    case CPUppl: return "CPU ppl";
        break;
    case CPUThreadP: return "CPU Thread pool";
        break;
    case GPU: return "GPU";
        break;
    }
    return "Not found";
}
