#include "canthread.h"
#include <zmq.hpp>

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

canThread::canThread(QObject *parent) : QThread(parent)
{  			 
}

void canThread::run(){
	zmq::context_t ctx(3);
    zmq::socket_t can_sub(ctx, ZMQ_SUB);
    can_sub.connect("tcp://127.0.0.1:5563");
    can_sub.setsockopt(ZMQ_SUBSCRIBE, "CAN", 3);

    while(!stop_flag){
        sensors::Can can;
        string topic=s_recv(can_sub);
        zmq::message_t msg;
        can_sub.recv(&msg);

        can.ParseFromArray(msg.data(), msg.size());

        int data_type=can.type();
        switch (data_type){
            case 688:
                emit send_handle(QString::number(can.data()));
                break;
            case 790:
                emit send_speed(can.data());
                break;
            case 1322:
                emit send_gear((int)can.data());
                break;
            case 1345:
                emit send_turn((int)can.data());
                break;
        }
    }
}

void canThread::stop(){
	stop_flag = true;
    emit send_end();
}