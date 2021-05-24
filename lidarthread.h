#ifndef LIDARTHREAD_H
#define LIDARTHREAD_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QTimer>
#include <QCoreApplication>

#include <unistd.h>
#include <atomic>
#include <cmath>
#include <csignal>
#include <cstdlib>
#include <chrono>

#include <Eigen/Eigen>
#include <fstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <vtkRenderWindow.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>
#include <pcl/filters/voxel_grid.h>

#include "jsoncpp/json/json.h"

#include "ouster/os1.h"
#include "ouster/os1_packet.h"
#include "ouster/os1_util.h"
#include "ouster/viz.h"

#include "Timestamp.h"
#include <google/protobuf/text_format.h>
#include "sensors.pb.h"
#include <zmq.hpp>
#include <fstream>

#define os1_host  "os1-991904000944.local"
#define os1_udp_dest   "10.5.5.1"


namespace OS1 = ouster::OS1;
namespace viz = ouster::viz;


class lidarThread : public QThread
{
    Q_OBJECT
public:
    explicit lidarThread(QObject *parent = 0);
    bool stop_flag = false;

    pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_cloud; //생성할 PointCloud structure구조체(x,y,z) 정의
    pcl::PointCloud<pcl::PointXYZ> cloud;

    ofstream file;

public slots:
    void stop();
private:
    void run() override;

signals:
    void send_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr);
};

#endif // LIDARTHREAD_H
