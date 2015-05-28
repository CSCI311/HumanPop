#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "Cell.h"
#include "SimulationSystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void loadMap();
    QGraphicsScene* scene;
    SimulationSystem* SimSys;

private slots:
    void updateSim();
};

#endif // MAINWINDOW_H
