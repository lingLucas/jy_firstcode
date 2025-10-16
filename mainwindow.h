#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <QTimer>

#include "imageview.h"
#include "hkcamera.h"
#include "camerause.h"
#include "cameramanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUi();
    void cleanVideoEvent();
    void cleanCameraEvent();
    void cleanEvents();
    void displayOpenCVImage(const cv::Mat &image);

private slots:
    void on_pushButton_opencam_clicked();

    void on_pushButton_openimg_clicked();

    void on_pushButton_openvideo_clicked();

    void readFrame();

    void workerFinished();

    void displayImage(const QImage &image);

    void logMessageOutput(const QString &msg);

    void on_pushButton_exit_clicked();


    void on_pushButton_getvalue_clicked();

    void on_pushButton_setvalue_clicked();

    void handleActionConnect();

    void handleActionDisconnect();

    void handleActionFind();

    void onSearchFinished(int deviceCount);

    void updateTimeDisplay(); // 更新时间的槽函数

private:
    Ui::MainWindow *ui;

    cv::VideoCapture cap;

    QTimer *timer;

    int frameCount;

    ImageView *imageView = nullptr;

    QThread *workerThread = nullptr;

    MV_CC_DEVICE_INFO_LIST  m_stDevList;

    HKCamera *hkCamera = nullptr;

    QThread *cameraThread = nullptr;

    CameraUse *cameraUse = nullptr;

    CameraManager *cameraManager = nullptr;

    bool is_init_camera;
    bool isconnect_camera;

};
#endif // MAINWINDOW_H
