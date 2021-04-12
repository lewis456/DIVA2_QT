#ifndef GPSTHREAD_H
#define GPSTHREAD_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <string>
#include <iostream>
#include <zmq.hpp>

#include "Timestamp.h"
#include "Strtok_m.h"
#include "Can_serial.h"

#define GPSDEVICE "/dev/ttyACM0"
#define BAUDRATE B9600


class gpsThread : public QThread
{
     Q_OBJECT
public:
    explicit gpsThread(QObject *parent = 0);

    bool stop_flag = false;
    double Convert_to_dd(double raw);

public slots:
    //void get_dir(QString);
    void stop();

private:
    void run() override;

signals:
    void send_ll(QString, QString);
    void send_end();

};

#endif // GPSTHREAD_H
