#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include "loggerfunc.h"
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // 启动日志系统
    // QString setpath = "logs/" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")+".log";
    QString setpath = "logs/" + QDateTime::currentDateTime().toString("yyyyMMdd")+".log";
    Logger::instance().setLogFilePath(setpath);
    Logger::instance().setMaxFileSize(10 * 1024 * 1024);
    Logger::instance().start();

    qInfo() << "主程序启动";
    w.setWindowTitle("棒管探伤检测系统");
    w.show();
    return a.exec();
}
