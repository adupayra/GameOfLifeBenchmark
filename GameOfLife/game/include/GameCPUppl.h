#pragma once
#include "Game.h"
#include <functional>

class GameCPUppl :
    public Game
{
private:
    void process();
    void processCell(int);
    std::function<void(int)> m_processCellref;
public:
    GameCPUppl(int dimension, int cellsPerDim) : Game(dimension, cellsPerDim) {};
};

