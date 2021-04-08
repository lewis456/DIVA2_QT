#include "gpsthread.h"
#include <zmq.hpp>
struct termios stOldState;
struct termios stNewState;

using namespace std;

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

gpsThread::gpsThread(QObject *parent) : QThread(parent)
{
    
}

void gpsThread::run() {
    zmq::context_t ctx(1);
    zmq::socket_t gps_sub(ctx, ZMQ_SUB);
    gps_sub.connect("tcp://127.0.0.1:5563");
    gps_sub.setsockopt(ZMQ_SUBSCRIBE, "GPS", 3);

    std::cout << "GPS streaming_start" << std::endl;

    while (!stop_flag) {
        string topic = s_recv(gps_sub);
        latitude= s_recv(gps_sub);
        longitude = s_recv(gps_sub);
        cout<<latitude<<" "<<longitude<<endl;
        emit send_ll(
            QString::fromLocal8Bit(latitude.c_str()),
            QString::fromLocal8Bit(longitude.c_str())
        );
       // QThread::msleep(1000);
    }
    //QCoreApplication::processEvents();
}

void gpsThread::stop(){
    stop_flag = true;
    emit send_end();
    writeFile.close();
    cs.close_serial(iDev);
}

void gpsThread::get_dir(QString dir_str){
    dir = dir_str.toStdString();
}

long double gpsThread::Convert_to_dd(long double raw){
    int dd = (int)(raw/100);
    long double ddddd = raw - (long double)(dd*100);
    ddddd /= 60;

    return (long double)dd+ddddd;
}
