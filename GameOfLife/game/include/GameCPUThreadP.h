#pragma once
#include "Game.h"
#include "ThreadPool.h"

class GameCPUThreadP :
    public Game
{
private:
    ThreadPool* m_threadPool;
    int m_cellsPerThread;
    int m_nThreads;
    void processCells(int start, int end);
    void process();

public:
    GameCPUThreadP(int, int);
    ~GameCPUThreadP() { delete m_threadPool; }
};

