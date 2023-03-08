#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <iostream>
#include <future>
#include "GameCPUThreads.h"

class ThreadPool
{
private:
	std::vector<std::thread> m_threads;
	std::mutex m_queueMutex;
	std::function<void(int, int)> m_processCellsFunction;
	bool m_stop = false;
	int m_nbThreads;
	std::queue<std::function<void()>> m_functionsQueue;
	std::condition_variable condition;

public:


	void threadLoop();

	ThreadPool(int nbThreads, void (GameCPUThreads::* processCellsFunction)(int, int), GameCPUThreads* instance);

	~ThreadPool();

	std::future<void> wakeThread(int startCell, int endCell);
};

