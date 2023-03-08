#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <iostream>
#include <future>
#include "GameCPUThreads.h"

class ThreadPool2
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


	void threadLoop() {
		while (true) {
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> lock(m_queueMutex);
				condition.wait(lock, [&]() {return !m_functionsQueue.empty() || m_stop; });
				if (m_stop)
					return;
				task = std::move(m_functionsQueue.front());
				this->m_functionsQueue.pop();
			}
			task();
		}
	}

	ThreadPool2(int nbThreads, void (GameCPUThreads::*processCellsFunction)(int, int), GameCPUThreads* instance) {
		m_processCellsFunction = std::bind(processCellsFunction, instance, std::placeholders::_1, std::placeholders::_2);

		m_nbThreads = nbThreads;
		for(int i = 0; i < nbThreads; i++) 
			m_threads.emplace_back(std::thread(&ThreadPool2::threadLoop, this));

	}

	~ThreadPool2() {
		{
			std::unique_lock<std::mutex> lock(m_queueMutex);
			m_stop = true;
			condition.notify_all();
		}

		for (int i = 0; i < m_nbThreads; i++) {
			m_threads[i].join();
		}
	}

	std::future<void> wakeThread(int startCell, int endCell) {
		std::function<void()> bindedFunction = std::bind(m_processCellsFunction, startCell, endCell);
		auto packagedFunction = std::make_shared<std::packaged_task<void()>>(bindedFunction);
		std::future<void> result = packagedFunction->get_future();
		{
			std::unique_lock<std::mutex> lock(m_queueMutex);
			m_functionsQueue.emplace([packagedFunction]() {(*packagedFunction)(); });
		}
		condition.notify_one();
		return result;

		return std::future<void>();
	}
};

