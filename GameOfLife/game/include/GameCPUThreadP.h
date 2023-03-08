#pragma once
#include "GameCPUThreads.h"
#include "ThreadPool.h"
#include "ThreadPool2.h"

class GameCPUThreadP :
    public GameCPUThreads
{
private:
    ThreadPool* m_threadPool;
    ThreadPool2* m_threadPool2;
    void process();

public:
    GameCPUThreadP(int, int);
    ~GameCPUThreadP() { delete m_threadPool; delete m_threadPool2; }
};

