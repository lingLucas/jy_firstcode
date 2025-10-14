#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/opencv.hpp>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    imageView = new ImageView();
    ui->setupUi(this);
    ui->pushButton_opencam->setIcon(QIcon(":/images/icons/open_camera.png"));
    ui->pushButton_openvideo->setIcon(QIcon(":/images/icons/open_video.png"));
    ui->pushButton_openimg->setIcon(QIcon(":/images/icons/open_picture.png"));
    ui->pushButton_opendir->setIcon(QIcon(":/images/icons/open_folder.png"));
    ui->pushButton_save->setIcon(QIcon(":/images/icons/save_img.png"));
    ui->pushButton_exit->setIcon(QIcon(":/images/icons/logout.png"));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::readFrame);
    frameCount = 0;



}

MainWindow::~MainWindow()
{
    if (workerThread) {
        workerThread->quit();
        workerThread->wait();
        delete workerThread;
    }
    delete imageView;
    delete ui;
}



void MainWindow::on_pushButton_opencam_clicked()
{

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
//     QString fileName = QFileDialog::getOpenFileName(this,
//                 "打开图片", QDir::homePath(),
//                 "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif *.tiff)");

//     if (!fileName.isEmpty()) {
//         // 使用OpenCV读取图片
//         cv::Mat image = cv::imread(fileName.toStdString());

//         if (!image.empty()) {
//             displayOpenCVImage(image);
// //            statusLabel->setText("已加载: " + QFileInfo(fileName).fileName());
//         } else {
//             QMessageBox::warning(this, "错误", "无法加载图片文件");
//         }
//     }

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
    QImage qimg = imageView->MatToQImage(frame);
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
