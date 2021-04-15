#include "camthread.h"
#include <zmq.hpp>

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}
camThread::camThread(QObject *parent) : QThread(parent)
{
    Compression_params.push_back(cv::IMWRITE_JPEG_QUALITY); //Select jpeg
    Compression_params.push_back(30);
}

void camThread::run(){
    std::cout<<"CAM Streaming_start"<<std::endl;
    zmq::context_t ctx(2);
     zmq::socket_t cam_sub( ctx, ZMQ_SUB);
    cam_sub.connect("tcp://127.0.0.1:5563");
    cam_sub.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3);
    if( !cap.isOpened() )
          QThread::msleep(10);

    while(!stop_flag){
        string topic=s_recv(cam_sub);
        
        cv::Mat frame;
        zmq::message_t rcv;
        cam_sub.recv(& rcv);
        vector<uchar> data;
        data.resize(rcv.size());
        memcpy(data.data(), rcv.data(), rcv.size());
        frame = cv::imdecode(data, cv::IMREAD_COLOR);

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        flip(frame, frame, 1);

        QImage image(frame.size().width, frame.size().height, QImage::Format_RGB888);
        memcpy(image.scanLine(0), frame.data, static_cast<size_t>(image.width() * image.height() * frame.channels()));
        emit send_qimage(image);
    }
}

void camThread::get_dir(QString dir_str){
    dir = dir_str.toStdString();
}
void camThread::stop(){
    stop_flag = true;
    writeFile.close();
    cap.release();
}
 // int rows, cols, type;
            // cv::Mat img;
            // void *data;
        
            // zmq::message_t rcv_msg;

            // cam_sub.recv(&rcv_msg,0); // rows
            // rows = *(int*)rcv_msg.data();
            // cam_sub.recv(&rcv_msg, 0); // cols
            // cols = *(int*)rcv_msg.data();
            // cam_sub.recv(&rcv_msg, 0); // type
            // type = *(int*)rcv_msg.data();
            // cam_sub.recv(&rcv_msg, 0); // data
            // data = (void*)rcv_msg.data();

           // QImage image(cols, rows, QImage::Format_RGB888);
        // memcpy(image.scanLine(0), data, static_cast<size_t>(cols*rows*3));
        // emit send_qimage(image);