#include "imuthread.h"
#include <zmq.hpp>

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

imuThread::imuThread(QObject *parent) : QThread(parent)
{	


}

void imuThread::run() {

    zmq::context_t ctx(3);
    zmq::socket_t imu_sub(ctx, ZMQ_SUB);
    imu_sub.connect( "tcp://127.0.0.1:5563");
    imu_sub.setsockopt(ZMQ_SUBSCRIBE,  "IMU", 3);
    cout<<"imu run"<<endl;
    while(!stop_flag) {
        string topic=s_recv(imu_sub);
        cout<<"recived data"<<endl;
        zmq::message_t msg;
        imu_sub.recv(&msg);
        ImuPacket imupacket=*(ImuPacket*)msg.data();
        // accel_x=imupacket.scaledAccelX;
        // accel_y=imupacket.scaledAccelY;
        // accel_y=imupacket.scaledAccelZ;
        accel_x=imupacket.get_x();
        accel_y=imupacket.get_y();
        accel_z=imupacket.get_z();
        emit send_acc(accel_x, accel_y, accel_z);
        printf("Accel (X,Y,Z) = (%.2f, %.2f, %.2f)\n",accel_x, accel_y, accel_z );
        //QThread::msleep(40);
    }
}


void imuThread::stop(){
	stop_flag = true;
}

void imuThread::get_dir(QString dir_str){
	dir = dir_str.toStdString();
}

ImuPacket::ImuPacket(){
    scaledAccelX=0;  scaledAccelY=0; scaledAccelZ=0;
    scaledGyroX=0; scaledGyroY=0; scaledGyroZ=0;
    scaledMagX=0; scaledMagY=0; scaledMagZ=0;
    estRoll=0; estPitch=0; estYaw=0;
    estRollUncert=NULL; estPitchUncert=NULL; estYawUncert=NULL;
}

float ImuPacket::get_x(){
    return scaledAccelX;
}
float ImuPacket::get_y(){
    return scaledAccelY;
}

float ImuPacket::get_z(){
    return scaledAccelZ;
}
