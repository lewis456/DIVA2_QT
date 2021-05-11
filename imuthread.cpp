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

    zmq::context_t ctx(2);
    zmq::socket_t imu_sub(ctx, ZMQ_SUB);
    imu_sub.connect( "tcp://127.0.0.1:5563");
    imu_sub.setsockopt(ZMQ_SUBSCRIBE,  "IMU", 3);
    cout<<"imu run"<<endl;
    while(!stop_flag) {
        sensors::Imu imu;
        string topic=s_recv(imu_sub);
        zmq::message_t msg;
        imu_sub.recv(&msg);

        //protobuf parsing
        imu.ParseFromArray(msg.data(), msg.size());
        accel_x=imu.scaledaccelx();
        accel_y=imu.scaledaccely();
        accel_z=imu.scaledaccelz();
        
        emit send_acc(accel_x, accel_y, accel_z);
    }
}


void imuThread::stop(){
	stop_flag = true;
}

void imuThread::get_dir(QString dir_str){
	dir = dir_str.toStdString();
}


// string msg_str(static_cast<char*>(msg.data()), msg.size());
//         imu.ParseFromString(msg_str);
