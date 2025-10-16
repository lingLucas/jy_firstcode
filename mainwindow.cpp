#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include "imageprocess.h"
#include "hkcamera.h"
#include "camerause.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    initUi();
}


MainWindow::~MainWindow()
{
    cleanEvents();
    delete ui;
}

void MainWindow::initUi()
{
    imageView = new ImageView();

    ui->pushButton_opencam->setIcon(QIcon(":/images/icons/open_camera.png"));
    ui->pushButton_openvideo->setIcon(QIcon(":/images/icons/open_video.png"));
    ui->pushButton_openimg->setIcon(QIcon(":/images/icons/open_picture.png"));
    ui->pushButton_opendir->setIcon(QIcon(":/images/icons/open_folder.png"));
    ui->pushButton_save->setIcon(QIcon(":/images/icons/save_img.png"));
    ui->pushButton_exit->setIcon(QIcon(":/images/icons/logout.png"));

    ui->pushButton_getvalue->setStyleSheet("QPushButton:hover {"
                                           // "   background-color: rgb(0, 247, 255);"
                                           "}");

    ui->pushButton_setvalue->setStyleSheet("QPushButton:hover {"
                                           // "   background-color: rgb(0, 247, 255);"
                                           "}");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimeDisplay);
    // connect(timer, &QTimer::timeout, this, &MainWindow::readFrame);
    frameCount = 0;
    connect(ui->actionFind, &QAction::triggered, this, &MainWindow::handleActionFind);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::handleActionConnect);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::handleActionDisconnect);
    is_init_camera = false;
    isconnect_camera = false;
    timer->start(1000);
}

void MainWindow::cleanVideoEvent()
{
    if (imageView) {
        imageView->stop();
    }
    if (workerThread) {
        workerThread->quit();
        if (!workerThread->wait(3000)) { // 等待5秒
            qDebug() << "Video worker thread did not finish, terminating.";
            workerThread->terminate();
            workerThread->wait();
        }
        delete workerThread;
        workerThread = nullptr;
    }
    imageView = nullptr;
    qDebug() << "Video worker thread closed.";
}

void MainWindow::cleanCameraEvent()
{
    if (cameraUse) {
        cameraUse->stop();
    }
    if (hkCamera) {
        hkCamera->StopGrabbing();
        hkCamera->Close();
        delete hkCamera; // 释放相机对象
        hkCamera = nullptr;
    }
    if (cameraThread) {
        cameraThread->quit();
        if (!cameraThread->wait(3000)) { // 等待最多3秒
            qDebug() << "Thread did not finish, forcing termination.";
            cameraThread->terminate();
            cameraThread->wait();
        }
        delete cameraThread;
        cameraThread = nullptr;
    }

    cameraUse = nullptr;
    HKCamera::FinalizeSDK();
    qDebug() << "Camera worker thread closed.";
}

void MainWindow::cleanEvents()
{
    cleanVideoEvent();
    cleanCameraEvent();
}


void MainWindow::updateTimeDisplay()
{
    // 获取当前时间并格式化
    QString timeString = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 在 Label 上显示
    ui->label_time->setText(timeString);

}

void MainWindow::on_pushButton_opencam_clicked()
{
    if(!is_init_camera || !isconnect_camera){
        qDebug() << "Please Connect Camera!!!";
        return;
    }
    int nRet;
    // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
    if (m_stDevList.pDeviceInfo[0]->nTLayerType == MV_GIGE_DEVICE)
    {
        unsigned int nPacketSize = 0;
        nRet = hkCamera->GetOptimalPacketSize(&nPacketSize);
        if (nRet == MV_OK)
        {
            nRet = hkCamera->SetIntValue("GevSCPSPacketSize",nPacketSize);
            if(nRet != MV_OK)
            {
                qDebug()<<"Warning: Set Packet Size fail!"<< nRet;
            }
        }
        else
        {
            qDebug()<<"Warning: Get Packet Size fail!"<< nRet;
        }
    }
    // ch:设置触发模式为off | eb:Set trigger mode as off
    nRet = hkCamera->SetEnumValue("TriggerMode", MV_TRIGGER_MODE_OFF);
    if (MV_OK != nRet)
    {
        qDebug()<< "Set Trigger Mode fail!"  <<nRet;
        return;
    }

    nRet = hkCamera->SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    if (MV_OK != nRet)
    {
        qDebug()<< "ExposureAuto fail!"  <<nRet;
        return;
    }

    // ch:开始取流 | en:Start grab image
    nRet = hkCamera->StartGrabbing();
    if (MV_OK != nRet)
    {
        qDebug()<<"Start Grabbing fail! "<< nRet;
        return;
    }

    if (cameraThread) {
        cameraUse->stop();
        cameraThread->quit();
        cameraThread->wait();
        // delete cameraUse;
        delete cameraThread;
        cameraThread = nullptr;
        cameraUse = nullptr;
    }

    // 创建线程和worker
    cameraThread = new QThread(this);
    cameraUse = new CameraUse();
    cameraUse->setCamera(hkCamera);
    cameraUse->moveToThread(cameraThread);

    connect(cameraThread, &QThread::started, cameraUse, &CameraUse::processCamera);
    connect(cameraUse, &CameraUse::sendImage, this, &MainWindow::displayImage);
    connect(cameraUse, &CameraUse::logMessage, this, &MainWindow::logMessageOutput);

    connect(cameraUse, &CameraUse::finished, cameraThread, &QThread::quit);
    connect(cameraThread, &QThread::finished, cameraUse, &QObject::deleteLater);

    cameraThread->start();

}


void MainWindow::displayOpenCVImage(const cv::Mat &image)
{
    // OpenCV使用BGR格式，Qt使用RGB格式，需要转换
    cv::Mat rgbImage;
    if (image.channels() == 3) {
        cv::cvtColor(image, rgbImage, cv::COLOR_BGR2RGB);
    } else if (image.channels() == 1) {
        cv::cvtColor(image, rgbImage, cv::COLOR_GRAY2RGB);
    } else {
        rgbImage = image.clone();
    }

    // 创建QImage
    QImage qimg(rgbImage.data, rgbImage.cols, rgbImage.rows,
               rgbImage.step, QImage::Format_RGB888);

    // QImage qimg = MatToQImage(image);

    // 创建QPixmap并显示
    QPixmap pixmap = QPixmap::fromImage(qimg);

    // 缩放图片以适应标签大小
    if (!pixmap.isNull()) {
        QSize labelSize = ui->imageLabel->size();
        QPixmap scaledPixmap = pixmap.scaled(
            labelSize.width(), labelSize.height(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // ✅ 设置 QLabel 内容居中
        ui->imageLabel->setAlignment(Qt::AlignCenter);
        ui->imageLabel->setPixmap(scaledPixmap);
    }
}


void MainWindow::on_pushButton_openimg_clicked()
{

    /*
    QString fileName = QFileDialog::getOpenFileName(this,
                "打开图片", QDir::homePath(),
                "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif *.tiff)");

    if (!fileName.isEmpty()) {
        // 使用OpenCV读取图片
        cv::Mat image = cv::imread(fileName.toStdString());

        if (!image.empty()) {
            displayOpenCVImage(image);
        // statusLabel->setText("已加载: " + QFileInfo(fileName).fileName());
        } else {
            QMessageBox::warning(this, "错误", "无法加载图片文件");
        }
    }*/


    QString filePath = QFileDialog::getOpenFileName(this,
                "打开图片", QDir::homePath(),
                "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif *.tiff)");
    if (filePath.isEmpty()) return;

    // qDebug() << "文件路径：" << filePath;
    imageView = new ImageView();
    imageView->setPath(filePath);

    bool success = connect(imageView, &ImageView::sendImage, this, &MainWindow::displayImage, Qt::QueuedConnection);
    connect(imageView, &ImageView::logMessage, this, &MainWindow::logMessageOutput);
    if (!success) {
        qDebug() << "信号与槽连接失败";
    }


    imageView->processImage();
}


void MainWindow::on_pushButton_openvideo_clicked()
{

    /*
    // QString fileName = QFileDialog::getOpenFileName(this,
    //                                                 "打开视频", QDir::homePath(),
    //                                                 "视频文件 (*.mp4 *.avi *.mov *.mkv *.wmv)");
    // if (fileName.isEmpty())
    //     return;

    // cap.open(fileName.toStdString());
    // frameCount = 0;
    // if (!cap.isOpened()) {
    //     QMessageBox::warning(this, "错误", "无法打开视频文件！" + fileName);
    //     return;
    // }

    // timer->start(33); // 每 33ms 约 30 FPS
    */

    QString filePath = QFileDialog::getOpenFileName(this, "选择视频文件", "", "Video Files (*.mp4 *.avi *.mov)");
    if (filePath.isEmpty()) return;

    // 若已有线程，先关闭
    if (workerThread) {
        imageView->stop();
        workerThread->quit();
        workerThread->wait();
        delete workerThread;
        workerThread = nullptr;
        imageView = nullptr;
    }

    // 创建线程和worker
    workerThread = new QThread(this);
    imageView = new ImageView();
    imageView->setPath(filePath);
    imageView->moveToThread(workerThread);

    connect(workerThread, &QThread::started, imageView, &ImageView::processVideo);
    connect(imageView, &ImageView::sendImage, this, &MainWindow::displayImage);
    connect(imageView, &ImageView::logMessage, this, &MainWindow::logMessageOutput);
    connect(imageView, &ImageView::finished, this, &MainWindow::workerFinished);
    connect(imageView, &ImageView::finished, workerThread, &QThread::quit);
    connect(workerThread, &QThread::finished, imageView, &QObject::deleteLater);

    workerThread->start();
}


void MainWindow::readFrame()
{
    cv::Mat frame;
    if (!cap.read(frame)) {
        timer->stop();
        cap.release();
        QMessageBox::information(this, "结束", "视频播放完毕！");
        return;
    }
    frameCount++;
    QImage qimg = ImageProcess::MatToQImage(frame);
    QString msg = QString("frame=%1 ,检测到缺陷数量%2").arg(frameCount).arg(20);
    logMessageOutput(msg);
    QPixmap pix = QPixmap::fromImage(qimg);
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->imageLabel->setPixmap(pix.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void MainWindow::logMessageOutput(const QString &msg)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->log_output->setFont(QFont("Consolas", 11));
    ui->log_output->appendPlainText(QString("[%1] %2").arg(time, msg));
}


void MainWindow::displayImage(const QImage &image) {
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image).scaled(
        ui->imageLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
}

void MainWindow::workerFinished() {
    QString msg = QString("视频播放完成");
    logMessageOutput(msg);
}

void MainWindow::on_pushButton_exit_clicked()
{
    cleanEvents();
    QApplication::quit();
}


void MainWindow::on_pushButton_getvalue_clicked()
{
    qDebug()<<"get value";
    if(!is_init_camera || !isconnect_camera){
        qDebug() << "Please Connect Camera!!!";
        return;
    }
    MVCC_FLOATVALUE stFloatValue = {0};
    int nRet = hkCamera->GetFloatValue("ExposureTime", &stFloatValue);
    if (MV_OK != nRet)
    {
        return;
    }
    float exposuretime_value = stFloatValue.fCurValue;


    nRet = hkCamera->GetFloatValue("Gain", &stFloatValue);
    if (MV_OK != nRet)
    {
        return;
    }
    float gain_value = stFloatValue.fCurValue;

    nRet = hkCamera->GetFloatValue("ResultingFrameRate", &stFloatValue);
    if (MV_OK != nRet)
    {
        return;
    }
    float frameRate_value = stFloatValue.fCurValue;

    // qDebug()<<"exposuretime_value:"<<exposuretime_value;
    // qDebug()<<"gain_value:"<<gain_value;
    // qDebug()<<"frameRate_value:"<<frameRate_value;
    ui->lineEdit_exporetime->setText(QString::number(exposuretime_value));
    ui->lineEdit_gain->setText(QString::number(gain_value));
    ui->lineEdit_framerate->setText(QString::number(frameRate_value));
}


void MainWindow::on_pushButton_setvalue_clicked()
{
    if(!is_init_camera || !isconnect_camera){
        qDebug() << "Please Connect Camera!!!";
        return;
    }

    hkCamera->SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);

    hkCamera->SetFloatValue("ExposureTime", (float)ui->lineEdit_exporetime->text().toDouble());

    hkCamera->SetEnumValue("GainAuto", 0);

    hkCamera->SetFloatValue("Gain", (float)ui->lineEdit_gain->text().toDouble());

    int nRet = hkCamera->SetBoolValue("AcquisitionFrameRateEnable", true);
    if (MV_OK != nRet)
    {
        return;
    }

    hkCamera->SetFloatValue("AcquisitionFrameRate", (float)ui->lineEdit_framerate->text().toDouble());
}


// 查找完成后的处理
void MainWindow::onSearchFinished(int deviceCount)
{
    if (deviceCount == 0) {
        qDebug() << "No devices found.";
        // 可以在UI上显示一个提示
    } else {
        // qDebug() << QString("Found %1 devices.").arg(deviceCount);
        QString msg = QString("Found %1 devices.").arg(deviceCount);
        logMessageOutput(msg);
    }
}

void MainWindow::handleActionFind()
{
    qDebug() << "Find clicked!";
    cameraManager = new CameraManager();
    bool success_is = connect(cameraManager, &CameraManager::logMessage, this, &MainWindow::logMessageOutput);
    success_is = connect(cameraManager, &CameraManager::searchFinished, this, &MainWindow::onSearchFinished);
    if (!success_is) {
        qDebug() << "信号与槽连接失败";
    }
    cameraManager->findCamDevice(&m_stDevList);
    is_init_camera = true;
}


void MainWindow::handleActionConnect()
{
    qDebug() << "Connect clicked!";
    if (!is_init_camera){
        qDebug()<<"camera not init!!!";
        return;
    }

    hkCamera = new HKCamera();
    int nRet = hkCamera->Open(m_stDevList.pDeviceInfo[0]);
    if (MV_OK != nRet)
    {
        delete hkCamera;
        hkCamera = NULL;
        qDebug()<<"Open Fail"<< nRet;
        return;
    }
    isconnect_camera = true;

}


void MainWindow::handleActionDisconnect()
{
    qDebug() << "Disconnect clicked!";
    if (!is_init_camera){
        qDebug()<<"camera not init!!!";
        return;
    }
    if (!isconnect_camera){
        return;
    }
    if (cameraUse) {
        cameraUse->stop();
    }
    if (hkCamera) {
        hkCamera->Close();
        delete hkCamera; // 释放相机对象
        hkCamera = nullptr;
    }
    if (cameraThread) {
        cameraThread->quit();
        if (!cameraThread->wait(3000)) { // 等待最多3秒
            qDebug() << "Thread did not finish, forcing termination.";
            cameraThread->terminate();
            cameraThread->wait();
        }
        delete cameraThread;
        cameraThread = nullptr;
    }
    cameraUse = nullptr;
    isconnect_camera = false;
}

