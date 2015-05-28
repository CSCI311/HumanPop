#include <iostream>
#include <cstdlib>
#include <string>


//the following line is necessary for the GetConsoleWindow() function to work!
//it basically says that you are running this program on Windows 2000 or higher



using namespace std;

#include "Mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
