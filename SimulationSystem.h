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

    int getTimeStep() const;
    void setTimeStep(int timeStep);

    double getBirthRate() const;
    void setBirthRate(double birthRate);

    double getDeathRate() const;
    void setDeathRate(double deathRate);

    unsigned long getTotal() const;

private:
    Map _map;
    MainWindow* _app;
    int _timeStep;

    double _birthRate;
    double _deathRate;

    long unsigned int _total;
};

