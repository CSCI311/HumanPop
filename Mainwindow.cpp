#include "Mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include "SimulationSystem.h"
#include <qtimer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SimSys = new SimulationSystem("map.bmp", this);

    loadMap();
    ui->graphicsView->setScene(scene);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSim()));
    timer->start(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadMap()
{
    scene = new QGraphicsScene();
    Map map = SimSys->getMap();
    for(int x = 0; x < map.getWidth() -1; x++ ) {
        for(int y =0; y < map.getHeight(); y++) {
            QGraphicsItem *item = map.getCell(x,y);
            item->setPos(QPointF(x*10, y*10));
            scene->addItem(item);
        }
    }
}

void MainWindow::addCell(Cell * newCell)
{
    QGraphicsItem*  item = newCell;
    item->setPos(QPointF(newCell->getX()*10, newCell->getY()*10));
    scene->addItem(item);
}

void MainWindow::deleteCell(Cell* item)
{
    scene->removeItem(item);
}

void MainWindow::updateSim()
{
    SimSys->runStep();
}
