#include "lidarthread.h"

inline static std::string s_recv(zmq::socket_t & socket, int flags = 0) {
    zmq::message_t message;
    socket.recv(& message, flags);

    return std::string(static_cast < char *> (message.data()), message.size());
}

lidarThread::lidarThread(QObject* parent) : QThread(parent)
{
    ptr_cloud.reset( new pcl::PointCloud<pcl::PointXYZ>);
}

void lidarThread::run(){
    zmq::context_t ctx(1);
    zmq::socket_t lidar_sub(ctx, ZMQ_SUB);
    lidar_sub.connect("tcp://127.0.0.1:5563");
    lidar_sub.setsockopt(ZMQ_SUBSCRIBE, "LIDAR", 5);

    while(!stop_flag){
        sensors::Lidar lidar;
        string topic=s_recv(lidar_sub);
        zmq::message_t msg;
        lidar_sub.recv(&msg);

        lidar.ParseFromArray(msg.data(), msg.size());
        int size=(int)lidar.size();
        cloud.resize(size);
        int i=0;
        for (auto & point : cloud) {
            point.x = lidar.data(i).x();
            point.y = lidar.data(i).y();
            point.z = lidar.data(i).z();
            i++;
        }
        *ptr_cloud=cloud;
        emit send_lidar(ptr_cloud);
        }
    QCoreApplication::processEvents();
}
void lidarThread::stop(){
    stop_flag = true;
}
