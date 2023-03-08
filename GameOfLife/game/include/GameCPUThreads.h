#pragma once
#include "Game.h"
#include <thread>

class GameCPUThreads :
    public Game
{
private:
    void process();

protected:
    int m_nThreads;
    int m_cellsPerThread;
public:
    void processCells(int, int);
    GameCPUThreads(int dimension, int cellsPerDim);
};

