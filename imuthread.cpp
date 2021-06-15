#include "imuthread.h"
#include <zmq.hpp>
#include <sys/time.h>
#include <cmath>

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
    
    file.open("imu_delay.csv");

    while(!stop_flag) {
        sensors::Imu imu;
        string topic=s_recv(imu_sub);
        zmq::message_t msg;
        imu_sub.recv(&msg);
        cout<<"recived\n";

        //protobuf parsing
        imu.ParseFromArray(msg.data(), msg.size());
        // accel_x=my_round(imu.scaledaccelx());
        // accel_y=my_round(imu.scaledaccely());
        // accel_z=my_round(imu.scaledaccelz());

        accel_x=imu.scaledaccelx();
        accel_y=imu.scaledaccely();
        accel_z=imu.scaledaccelz();
        
        struct timeval tv;
        gettimeofday(&tv, NULL);
        double cur=1000000*tv.tv_sec + tv.tv_usec;
        file<<cur-imu.timestamp()<<",us\n";

        emit send_acc(accel_x, accel_y, accel_z);
    }
}

float imuThread::my_round(float num){
    return round(num*100)/100;
}

void imuThread::stop(){
	stop_flag = true;
    file.close();
}

// string msg_str(static_cast<char*>(msg.data()), msg.size());
//         imu.ParseFromString(msg_str);
