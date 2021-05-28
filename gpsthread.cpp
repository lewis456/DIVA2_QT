#include "gpsthread.h"
#include <zmq.hpp>
#include <sys/time.h>
// struct termios stOldState;
// struct termios stNewState;

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

    file.open("gps_delay.csv");
    while (!stop_flag) {
        string topic = s_recv(gps_sub);
        sensors::Gps gps;
        zmq::message_t msg;
        gps_sub.recv(&msg);
        //protobuf parsing
        gps.ParseFromArray(msg.data(), msg.size());
        latitude = gps.latitude();
        longitude = gps.longitude();
        hdop=gps.horizontaldilutionofprecision();
        //cout<<gps.latitude()<<" "<<gps.longitude()<<endl;

        struct timeval tv;
        gettimeofday(&tv, NULL);
        double cur=1000000*tv.tv_sec + tv.tv_usec;
        file<<cur-gps.timestamp()<<",us\n";

        //printf("lat=%lf long=%lf\n", Convert_to_dd(latitude), Convert_to_dd(longitude));
        emit send_ll(
            QString::number(Convert_to_dd(latitude), 'g', 9),
            QString::number(Convert_to_dd(longitude), 'g', 9),
            hdop
        );

    }
}

void gpsThread::stop(){
    stop_flag = true;
    file.close();
    //emit send_end();
}

double gpsThread::Convert_to_dd(double raw){
    int dd = static_cast<int>(raw/100);
    double ddddd = (raw - static_cast<double>(dd*100))/60;

    return static_cast<double>(dd+ddddd);
}
