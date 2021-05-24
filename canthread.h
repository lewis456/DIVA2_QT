#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>

#include <iostream>
#include <cstring>
#include <fstream>

#include "Timestamp.h"
#include <google/protobuf/text_format.h>
#include "sensors.pb.h"

class CANdata {
public:
    CANdata(QObject *parent = 0){
        handle_angle = 0;
        vehicle_speed = 0;
        gear = 0;
        turn_indicator = 2;
    }
    int handle_angle, vehicle_speed,gear, turn_indicator;
};


class canThread : public QThread
{
	Q_OBJECT

public:
    canThread(QObject *parent = 0);

    bool stop_flag = false;

    ofstream file;

signals:
	void send_speed(float);
	void send_handle(QString);
	void send_gear(int);
	void send_turn(int);
	void send_end();

public slots:
	void stop();
private:
    void run() override;
};

#endif // CANTHREAD_H
