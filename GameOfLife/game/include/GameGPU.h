#pragma once
#include "Game.h"
class GameGPU :
    public Game
{
public:
    GameGPU(int dimensions, int cellsPerDim);
    ~GameGPU();
private:
    void process();
    uint8_t* m_devCells;
    uint8_t* m_devNewCells;
    int m_nbBlocks;
    int m_nbThreads;


};

