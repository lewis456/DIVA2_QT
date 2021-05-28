#include "camthread.h"
#include <zmq.hpp>
#include <time.h>
#include <sys/time.h>
#include <iomanip>

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
    zmq::context_t ctx(1);
     zmq::socket_t cam_sub( ctx, ZMQ_SUB);
    cam_sub.connect("tcp://127.0.0.1:5563");
    cam_sub.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3);
    if( !cap.isOpened() )
          QThread::msleep(10);


    file.open("cam_delay.csv");
    while(!stop_flag){
        struct timespec begin, end;
        double tmp=0.0;
        sensors::Cam cam;
        string topic=s_recv(cam_sub);
        
        zmq::message_t msg;
        cam_sub.recv(&msg);
        cv::Mat frame;

        //NO USE PROTOBUF
        // vector<uchar> imgdata;
        // imgdata.resize(msg.size());
        // memcpy(imgdata.data(), msg.data(), imgdata.size());

        // frame=cv::imdecode(imgdata, cv::IMREAD_COLOR);
    

        //protobuf parsing
        cam.ParseFromArray(msg.data(), msg.size());

        struct timeval tv;
        gettimeofday(&tv, NULL);
        double cur=1000000*tv.tv_sec + tv.tv_usec;
        file<<cur-cam.timestamp()<<",us\n";

        frame.create(cam.rows(), cam.cols(), CV_8UC3);
        std::cout<<"rows:"<<cam.rows()<<"/cols:"<<cam.cols()<<std::endl;
         memcpy((void*)frame.data, (void*)(&cam.image_data()[0]), frame.step[0]*(size_t)frame.rows);

         cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
         //flip(frame, frame, 1);

         QImage image(frame.size().width, frame.size().height, QImage::Format_RGB888);
         memcpy(image.scanLine(0), frame.data, static_cast<size_t>(image.width() * image.height() * frame.channels()));
         emit send_qimage(image);
         
    }
}
void camThread::stop(){
    stop_flag = true;
    file.close();
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

        // vector<uchar> data(cam.data().begin(), cam.data().end());

        // clock_gettime(CLOCK_MONOTONIC, &begin);
        // frame = cv::imdecode(data, cv::IMREAD_COLOR);
        // clock_gettime(CLOCK_MONOTONIC, &end);

        // long time = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec);
        // printf("Time (Milli): %lf\n", (double)time/1000000);
