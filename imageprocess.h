#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>
#include <QThread>

using namespace cv;

class ImageProcess
{
public:
    ImageProcess();
    ~ImageProcess();

    static Mat QImageToCvMat(const QImage &image, bool cloneImageData = true);
    static QImage MatToQImage(const Mat& mat);
};

#endif // IMAGEPROCESS_H
