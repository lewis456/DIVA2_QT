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

    zmq::context_t ctx(1);
    zmq::socket_t imu_sub(ctx, ZMQ_SUB);
    imu_sub.connect( "tcp://127.0.0.1:5564");
    imu_sub.setsockopt(ZMQ_SUBSCRIBE,  "IMU", 3);
    cout<<"imu run"<<endl;
    while(!stop_flag) {
        string topic=s_recv(imu_sub);
        cout<<"recived data"<<endl;
        zmq::message_t msg;
        imu_sub.recv(&msg);
        ImuPacket imupacket=*(ImuPacket*)msg.data();
        accel_x=imupacket.scaledAccelX;
        accel_y=imupacket.scaledAccelY;
        accel_y=imupacket.scaledAccelZ;
        emit send_acc(accel_x, accel_y, accel_z);

        QThread::msleep(40);
    }
}


void imuThread::stop(){
	stop_flag = true;
}

void imuThread::get_dir(QString dir_str){
	dir = dir_str.toStdString();
}
