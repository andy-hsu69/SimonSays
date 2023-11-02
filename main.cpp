#include "mainwindow.h"
#include <SimonModel.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimonModel model;
    MainWindow w(model);
    w.show();
    return a.exec();
}
