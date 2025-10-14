#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <QTimer>

#include "imageview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayOpenCVImage(const cv::Mat &image);



private slots:
    void on_pushButton_opencam_clicked();

    void on_pushButton_openimg_clicked();

    void on_pushButton_openvideo_clicked();

    void readFrame();

    void workerFinished();

    void displayImage(const QImage &image);

    void logMessageOutput(const QString &msg);

private:
    Ui::MainWindow *ui;

    cv::VideoCapture cap;

    QTimer *timer;

    int frameCount;

    ImageView *imageView = nullptr;

    QThread *workerThread = nullptr;

};
#endif // MAINWINDOW_H
