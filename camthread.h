#ifndef CAMTHREAD_H
#define CAMTHREAD_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QDebug>
#include <iostream>
#include <QCoreApplication>

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>

#include "Timestamp.h"
#include "sensors.pb.h"

class camThread : public QThread
{
    Q_OBJECT
public:
    explicit camThread(QObject *parent = 0);
    Timestamp ts;

    cv::VideoCapture cap;
    cv::Mat frame;
    cv::Mat mat;
    char buf[256];

    int rows, cols;
    vector<uchar> data;

    vector<int> Compression_params;
    bool stop_flag = false;

public slots:
    void stop();

private:
    void run() override;
signals:
    void send_qimage(QImage);

};

#endif // CAMTHREAD_H
