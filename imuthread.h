#ifndef IMUTHREAD_H
#define IMUTHREAD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <string>
#include <iostream>

#include "mscl/mscl.h"
#include "Timestamp.h"
class ImuPacket {
public:
    ImuPacket();
    float scaledAccelX, scaledAccelY, scaledAccelZ;
    float scaledGyroX, scaledGyroY, scaledGyroZ;
    float scaledMagX, scaledMagY, scaledMagZ;
    float estRoll, estPitch, estYaw;
    float estRollUncert, estPitchUncert, estYawUncert;

};

// ImuPacket::ImuPacket(){
//     scaledAccelX=0;  scaledAccelY=0; scaledAccelZ=0;
//     scaledGyroX=0; scaledGyroY=0; scaledGyroZ=0;
//     scaledMagX=0; scaledMagY=0; scaledMagZ=0;
//     estRoll=0; estPitch=0; estYaw=0;
//     estRollUncert=NULL; estPitchUncert=NULL; estYawUncert=NULL;
// }

class imuThread : public QThread
{
	Q_OBJECT
public:
    imuThread(QObject *parent = 0);

    Timestamp ts;
    bool stop_flag = false;
    string dir;
    float accel_x = 0.1;
	float accel_y = 0.1;
	float accel_z = 0.1;

	const char * mtime;
    char fp[526];
    string path;
    ofstream writeFile;

private slots:
    void get_dir(QString);
    void stop();

private:
	void run() override;
signals : 
	void send_acc(float, float, float);
    

};

#endif // IMUTHREAD_H
