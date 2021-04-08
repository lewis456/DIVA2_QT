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

    // path = dir+"/CAM/i30_CAM_ts_"+ts.getMilliTime()+".txt";
    // writeFile.open(path.c_str());
    // std::cout<<"The CAM_ts.txt file saved to ["<<path<<"]\n";
    // cap.open(2);
    // cap.read(frame);
    // cap.set(cv::CAP_PROP_FRAME_WIDTH, 4000);
    // cap.set(cv::CAP_PROP_FRAME_HEIGHT, 4000);
    // cap.read(frame);
    zmq::context_t ctx(1);
     zmq::socket_t cam_sub( ctx, ZMQ_SUB);
    cam_sub.connect("tcp://127.0.0.1:5563");
    cam_sub.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3);
    if( !cap.isOpened() )
          QThread::msleep(10);

    while(!stop_flag){
        //cap >> frame;

        // string m_time = ts.getMilliTime();
        // const char * now_time = ts.p_time();
        // //sprintf(buf,"/home/kanakim/Documents/CAM/JPG/i30_CAM_%s.jpg", now_time);
        // string save_path = dir+"/CAM/JPG/i30_CAM_"+m_time+".jpg";
        // string tmp = "\n";

        // cvtColor(frame, mat,cv::COLOR_BGR2RGB);
        int cnt = 0;
        string topic=s_recv(cam_sub);
            int rows, cols, type;
            cv::Mat img;
            void *data;
        
            zmq::message_t rcv_msg;

            cam_sub.recv(&rcv_msg,0); // rows
            rows = *(int*)rcv_msg.data();
            cam_sub.recv(&rcv_msg, 0); // cols
            cols = *(int*)rcv_msg.data();
            cam_sub.recv(&rcv_msg, 0); // type
            type = *(int*)rcv_msg.data();
            cam_sub.recv(&rcv_msg, 0); // data
            data = (void*)rcv_msg.data();
            //std::cout << "rows=" << rows << ", cols=" << cols << ", type=" << type << std::endl;

            if (type == 2) {
                img = cv::Mat(rows, cols, CV_8UC1, data);
            }
            else {
                img = cv::Mat(rows, cols, CV_8UC3, data);
            }
        QImage image(img.size().width, img.size().height, QImage::Format_RGB888);
        memcpy(image.scanLine(0), img.data, static_cast<size_t>(image.width() * image.height() * 3));
        emit send_qimage(image);

        // if(writeFile.is_open()){
        //     writeFile << m_time << "\n";
        // }
        // imwrite(save_path.c_str(), frame, Compression_params);
        //imwrite(save_path.c_str(), frame);
        
        //QThread::msleep(10);
        //QCoreApplication::processEvents();
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
