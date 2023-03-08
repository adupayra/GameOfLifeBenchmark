#pragma once
#include "Game.h"
#include <thread>

class GameCPUThreads :
    public Game
{
private:
    void process();
    int m_nThreads;
    int m_cellsPerThread;
    void processCells(int, int);

public:
    GameCPUThreads(int dimension, int cellsPerDim);
};

