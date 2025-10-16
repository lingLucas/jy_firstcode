#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("棒管探伤检测系统");
    w.show();
    return a.exec();
}
