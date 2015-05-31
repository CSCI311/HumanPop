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
    SimSys->setTimeStep(10);

    loadMap();
    ui->graphicsView->setScene(scene);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSim()));
    timer->start(15);

    QTimer *tim2 = new QTimer(this);
    connect(tim2, SIGNAL(timeout()), this, SLOT(updateResult()));
    tim2->start(1000);
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
            item->setPos(QPointF(x*5, y*5));
            if(map.getCell(x,y)->tileType() != '.')
                scene->addItem(item);
        }
    }
}

void MainWindow::addCell(Cell * newCell)
{
    QGraphicsItem*  item = newCell;
    if(ui->updateDisplay->isChecked()) {
        item->setPos(QPointF(newCell->getX()*5, newCell->getY()*5));
        scene->addItem(item);
    }
}

void MainWindow::deleteCell(Cell* item)
{
    if(ui->updateDisplay->isChecked())
            scene->removeItem(item);
}

void MainWindow::updateSim()
{
    SimSys->runStep();
}

void MainWindow::on_yearPerStep_editingFinished(int val)
{
    SimSys->setTimeStep(this->ui->yearPerStep->value());
}

void MainWindow::on_yearPerStep_valueChanged(int arg1)
{
    SimSys->setTimeStep(arg1);
}

void MainWindow::on_birthRate_valueChanged(double arg1)
{
    SimSys->setBirthRate(arg1);
}

void MainWindow::on_updateDisplay_toggled(bool checked)
{
    if(checked == true) {
        Map map = SimSys->getMap();

        for(int x = 0; x < map.getWidth() -1; x++ ) {
            for(int y =0; y < map.getHeight(); y++) {
                QGraphicsItem *item = map.getCell(x,y);
                item->setPos(QPointF(x*5, y*5));
                if(item->scene() != scene)
                    scene->addItem(item);
            }
        }
    }
}

void MainWindow::updateResult()
{
    ui->lcdNumber->display((int)SimSys->getTotal());
}
