#pragma once
//#include "Agent.h"
#include "Map.h"
#include <string>
#include "Mainwindow.h"

using namespace std;

class MainWindow;

class SimulationSystem
{
public:
    SimulationSystem(string mapFileName, MainWindow* main);

    void runStep();

    Map& getMap();

private:
    Map _map;
    MainWindow* _app;
};

