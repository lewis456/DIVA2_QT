#include "mainwindow.h"
#include "ui_mainwindow.h"

bool wifi_use = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1776,900);
    storage=QStorageInfo::root();
    ui->progressBar->setRange(0,100);
//    ui->progressBar->setValue(50);
    timer=new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(setUsage()));
    //QThread::msleep(1000);
    qRegisterMetaType<pcl::PointCloud<pcl::PointXYZ>::Ptr >("pcl::PointCloud<pcl::PointXYZ>::Ptr");
    gpscnt = 0;
    connect(ui->actionInitializing, SIGNAL(triggered()), this, SLOT(Initializing_for_Live()));  
    //connect(ui->actionLive_Streaming, SIGNAL(triggered()), this, SLOT(sensing_start()));
    connect(ui->actionInitializing_2, SIGNAL(triggered()), this, SLOT(Initializing_for_Playback()));  
    //connect(ui->actionStreaming_End, SIGNAL(triggered()), this, SLOT(sensing_stop()));
}

MainWindow::~MainWindow()
{
    database.close();
    delete ui;
}

void MainWindow::on_gps_cb_stateChanged(int arg1){
    if(arg1 > 0){
        use_gps = true;
    }else{
        use_gps = false;
    }
}

void MainWindow::on_cam_cb_stateChanged(int arg1){
    if(arg1 > 0){
        use_cam = true;
    }else{
        use_cam = false;
    }
}

void MainWindow::on_lidar_cb_stateChanged(int arg1){
    if(arg1 > 0){
        use_lidar = true;
    }else{
        use_lidar = false;
    }

}

void MainWindow::on_imu_cb_stateChanged(int arg1){
    if(arg1 > 0){
        use_imu = true;
    }else{
        use_imu = false;
    }

}

void MainWindow::on_can_cb_stateChanged(int arg1){
    if(arg1 > 0){
        use_can = true;
    }else{
        use_can = false;
    }

}


void MainWindow::display_gps_info(QString latitude, QString longitude,double hdop){
    //mpage->setView(mview);
    QString latlong="lat : "+latitude+" lng : "+longitude;
    //string latlong = " lat : "+latitude.toStdString()+" lng : "+longitude.toStdString();
    cout<<"signal lat="<<latitude.toStdString()<<" long= "<<longitude.toStdString();

    if(latitude != "0" && longitude != "0"){
        //gpsWidget2->setText(QString::fromLocal8Bit(latlong.c_str()));
        gpsWidget2->setText(latlong);
        if(wifi_use){
            mpage->runJavaScript(QString("addMarker(%1, %2);").arg(latitude).arg(longitude));  
                    if(gpscnt==0 || gpscnt%10 == 0){
                    mpage->runJavaScript(QString("getAddr();"),[this](const QVariant &v){
                        addr = v.toString();
                        gpsWidget->setText(addr);
                    });
            } 
        }
        gpsWidget2->show();
        gpsWidget->show();
        mview->show();
    }
    mview->show();

    if(gpscnt%10==0){
        if(hdop<=1){
            ui->signal1->setStyleSheet("QLabel { background-color: rgb(115, 210, 22); "
                                            "border-radius: 5px;}");
            ui->signal2->setStyleSheet("QLabel { background-color: rgb(115, 210, 22); "
                                            "border-radius: 5px;}");
            ui->signal3->setStyleSheet("QLabel { background-color: rgb(115, 210, 22); "
                                            "border-radius: 5px;}");
        }
        else if(hdop<=5){
            ui->signal1->setStyleSheet("QLabel { background-color: rgb(237, 212, 0); "
                                            "border-radius: 5px;}");
            ui->signal2->setStyleSheet("QLabel { background-color: rgb(237, 212, 0); "
                                            "border-radius: 5px;}");
            ui->signal3->setStyleSheet("QLabel { background-color: rgb(255, 255, 255); "
                                            "border-radius: 5px;}");
        }
        else{
            ui->signal1->setStyleSheet("QLabel { background-color: rgb(204, 0, 0); "
                                            "border-radius: 5px;}");
            ui->signal2->setStyleSheet("QLabel { background-color: rgb(255, 255, 255); "
                                            "border-radius: 5px;}");
            ui->signal3->setStyleSheet("QLabel { background-color: rgb(255, 255, 255); "
                                            "border-radius: 5px;}");
        }
        ui->signal1->show();
        ui->signal2->show();
        ui->signal3->show();
    }
    gpscnt++;
}

void MainWindow::gps_view_initialize(){
    if(wifi_use){
        mpage->runJavaScript(QString("resetMarker();"));
        mpage->runJavaScript(QString("initMap();"));
        mview->show();
    } 
    //QCoreApplication::processEvents();
}

void MainWindow::display_cam(QImage image){
    camWidget->setPixmap(QPixmap::fromImage(image).scaled(camWidget->width(),camWidget->height(), Qt::KeepAspectRatio));
    camWidget->setAlignment(Qt::AlignCenter);
    camWidget->show();
    QCoreApplication::processEvents();
}

void MainWindow::display_handle_data(QString str){
    str.prepend("Handle degree\n");
    //str.append("\n");
    // str.append("\nHandle acceleration : ");
    // str.append(str2);
    //str.sprintf("%3d", str);
    ui->label_5->setText(str);
    ui->label_5->show();
    QCoreApplication::processEvents();
}

void MainWindow::speedChanged(float value){
    mSpeedNeedle->setCurrentValue(value);
    QCoreApplication::processEvents();
}

void MainWindow::display_gear(int gear){
    if(gear == 1){//P
        redRectLabel->move(1306, 245);
    }else if(gear == 2){//R
        redRectLabel->move(1356, 245);
    }else if(gear == 3){//N
        redRectLabel->move(1406, 245);
    }else if(gear == 4){//D
        redRectLabel->move(1456, 245);
    }else{
        return;
    }
    QCoreApplication::processEvents();
}

void MainWindow::display_turn_indicator(int turn){
    if(turn == 1){//left
        lArrowLabel->show();
        rArrowLabel->hide();
    }else if(turn == 2){//right
        rArrowLabel->show();
        lArrowLabel->hide();
    }else if(turn == 0){//none
        lArrowLabel->hide();
        rArrowLabel->hide();
    }
    else if(turn==3){
        lArrowLabel->show();
        rArrowLabel->show();
    }
    QCoreApplication::processEvents();
}


void MainWindow::Make(){

    ui->progressBar->setMaximum(100);
    lvw = new lidarVTKWidget(this);
    camWidget=ui->Cam;
    gpsWidget = new QLabel(this);
    gpsWidget2 = new QLabel(this);
    mpage = new QWebEnginePage(this);
    mview = new QWebEngineView(this);
    iw = new imuWidget();
    mSpeedGauge = new QcGaugeWidget;
    
    QPixmap lpix("/home/yh/DIVA2_QT/resource/leftarrowbefore.png");
    QPixmap rpix("/home/yh/DIVA2_QT/resource/rightarrowbefore.png");
    ui->label->setPixmap(rpix);
    ui->label_2->setPixmap(lpix);
    
   QPixmap redRectPixm("/home/yh/DIVA2_QT/resource/square.png");
   redRectLabel = new QLabel(this);
   redRectLabel->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 0); }");
   redRectLabel->setPixmap(redRectPixm);
   redRectLabel->resize(35,35);
   redRectLabel->move(1306, 245); //p
   redRectLabel->raise();
   redRectLabel->show();


    QPixmap lArrowPixm("/home/yh/DIVA2_QT/resource/leftarrow.png");
    QPixmap rArrowPixm("/home/yh/DIVA2_QT/resource/rightarrow.png");
    lArrowLabel  = new QLabel(this); lArrowLabel->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 0); }");
    rArrowLabel = new QLabel(this); rArrowLabel->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 0); }");
    lArrowLabel->setPixmap(lArrowPixm);
    lArrowLabel->setGeometry(1300,280,80,80);
    rArrowLabel->setPixmap(rArrowPixm);
    rArrowLabel->setGeometry(1420,280,80,80);
    lArrowLabel->hide(); rArrowLabel->hide();

    //lidar widget
    ui->gridLayout_2->layout()->addWidget(lvw);
 
    //kakao map
    mview->setGeometry(650, 30, 580, 810);
    //mview->setAttribute(Qt::WA_TranslucentBackground);
    mview->setStyleSheet("background:transparent;");
    mpage->setUrl(QUrl("http://localhost:8080/map.html"));
    mpage->setBackgroundColor(Qt::transparent);
    mpage->setView(mview);

    gpsWidget->setGeometry(650, 815, 570, 40);
    gpsWidget->setStyleSheet("background-color: rgba(255, 255, 255, 80);");
    gpsWidget->setAlignment(Qt::AlignCenter);
    gpsWidget->raise();
    gpsWidget2->setGeometry(650, 855, 570, 40);
    gpsWidget2->setStyleSheet("background-color: rgba(255, 255, 255, 80);");
    gpsWidget2->setAlignment(Qt::AlignCenter);
    gpsWidget2->raise();

    //imu widget
    ui->gridLayout_3->layout()->addWidget(iw);

    //can widget
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);
    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::gray);
    bkg2->addColor(1.0,Qt::darkGray);
    mSpeedGauge->addArc(55);
    mSpeedGauge->addDegrees(65)->setValueRange(0,120);
    mSpeedGauge->addColorBand(50);
    mSpeedGauge->addValues(80)->setValueRange(0,120);
    mSpeedGauge->addLabel(70)->setText("Km/h");
    QcLabelItem *lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,120);
    mSpeedGauge->addBackground(15);
    mSpeedGauge->addGlass(88);
    ui->gridLayout->layout()->addWidget(mSpeedGauge);

    ui->signal1->show();
    ui->signal2->show();
    ui->signal3->show();

    ui->signal1->raise();
    ui->signal2->raise();
    ui->signal3->raise();
    //storage
    setUsage();

}


void MainWindow::Initializing_for_Live(){
    this->Make();
    mview->show();
    if(use_gps)
        gt = new gpsThread(this);
    if(use_cam)
        ct = new camThread(this);
    if(use_lidar)
        lt = new lidarThread(this);
    if(use_imu){
        it = new imuThread(this);
    }
    if(use_can)
       cant = new canThread();

    QString live_str= "Date : ";
    live_str.append(QString::fromLocal8Bit(ts.getDate().c_str()));
    ui->label_7->setText(live_str);

    if(use_gps){
        connect(ui->actionLive_Streaming, SIGNAL(triggered()), gt, SLOT(start()));
        connect(gt, SIGNAL(send_ll(QString, QString, double)), this, SLOT(display_gps_info(QString, QString, double))); 
        connect(ui->actionStreaming_End, SIGNAL(triggered()), gt, SLOT(stop()));
        connect(gt, SIGNAL(send_end()), this, SLOT(gps_view_initialize()));
    }
    
    if(use_cam){
        connect(ui->actionLive_Streaming, SIGNAL(triggered()), ct, SLOT(start()));
        connect(ct, SIGNAL(send_qimage(QImage)), this, SLOT(display_cam(QImage)));
        connect(ui->actionStreaming_End, SIGNAL(triggered()), ct, SLOT(stop()));
    }
    if(use_lidar){
        connect(ui->actionLive_Streaming, SIGNAL(triggered()), lt, SLOT(start()));
        connect(ui->actionLive_Streaming, SIGNAL(triggered()), lvw, SLOT(init()));
        connect(lt, SIGNAL(send_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr)), lvw, SLOT(display_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr)));
        connect(ui->actionStreaming_End, SIGNAL(triggered()), lt, SLOT(stop()));
    }
    if(use_imu){
        connect(ui->actionLive_Streaming, SIGNAL(triggered()), it, SLOT(start()));
        connect(it, SIGNAL(send_acc(float, float, float)), iw, SLOT(streaming_start(float,float,float)));
        connect(it, SIGNAL(send_acc(float,float,float)), this, SLOT(display_imu_xyz(float, float, float)));
        connect(ui->actionStreaming_End, SIGNAL(triggered()), it, SLOT(stop()));

    }
    if(use_can){
        connect(ui->actionLive_Streaming, SIGNAL(triggered()), cant, SLOT(start()));
        connect(cant, SIGNAL(send_handle(QString)),this, SLOT(display_handle_data(QString)));
        connect(cant, SIGNAL(send_speed(float)),this, SLOT(speedChanged(float)));
        connect(cant, SIGNAL(send_gear(int)), this, SLOT(display_gear(int)));
        connect(cant, SIGNAL(send_turn(int)), this, SLOT(display_turn_indicator(int)));
        connect(ui->actionStreaming_End, SIGNAL(triggered()), cant, SLOT(stop()));
        connect(cant, SIGNAL(send_end()), cant, SLOT(deleteLater()));
    }
    
}

void MainWindow::start_can_streaming(){
    cout<<"here"<<endl;
}  

void MainWindow::initial_map(){
    mpage->setUrl(QUrl("http://localhost:8080/map.html"));
    //mpage->setView(mview);
}

void MainWindow::Initializing_for_Playback(){
    this->Make();
    mview->show();

    if(this->setting_DB()){
        connect(ui->actionGet_Log, SIGNAL(triggered()), this, SLOT(get_log_token()));
        connect(ui->actionGet_Log, SIGNAL(triggered()), lvw, SLOT(init()), Qt::QueuedConnection);
        connect(this, SIGNAL(send_pcd(QString)), lvw, SLOT(display_pcd(QString)));
        connect(this, SIGNAL(send_imu(float, float, float)), iw, SLOT(streaming_start(float,float,float)));
        connect(ui->actionFinish, SIGNAL(triggered()), this, SLOT(Display_Stop()));
    }else{
        std::cout<<"Can't connect to DB"<<std::endl;
    }
}


struct MainWindow::CurrentLog
{
    QString t;
    QString v;
    QString d;
};

//id MainWindow::get_log_token(){    cout<<"log_displayed"<<endl;}

void MainWindow::get_log_token(){
    cout<<"get_log_token start"<<endl;
    ui->Date_list->clear();
    this_is_get_log = true;
    this->log_from_db = new QSqlQuery(this->database);
    this->log_from_db->exec("SELECT * FROM LOG;");
    MainWindow::CurrentLog current_log;
    this->log_from_db->first();
    
    while(1){
        if(this->log_from_db->next()){
            current_log.t = this->log_from_db->value(0).toString();
            current_log.v = this->log_from_db->value(2).toString();
            current_log.d =  this->log_from_db->value(1).toString();
            logs.push_back(current_log);
            ui->Scene_list->addItem(current_log.d);
        }else break;
    }
    cout<<"get_log_token end"<<endl;
}

void MainWindow::Display_Scene(QString Text){
    cout<<"Display_Scene_Start"<<endl;
    this->scene_from_db = new QSqlQuery(this->database);
    cout<<"1"<<endl;
    QString selectq = "SELECT * FROM SCENE WHERE log_token = '";
    cout<<"2"<<endl;
    selectq.append(Text);
    cout<<"3"<<endl;
    selectq.append("';");
    cout<<"4"<<endl;
    this->scene_from_db->exec(selectq);
    cout<<"5"<<endl;
    scenes_ftoken.clear();
    cout<<"6"<<endl;
    scenes_nbrframes.clear();
    cout<<"7"<<endl;
    int idx = 0;
    while(1){
        cout<<"while start"<<endl;
        if(this->scene_from_db->next()){
            cout<<"8"<<endl;
            scenes_ftoken.push_back(this->scene_from_db->value(0).toString());
            cout<<"9"<<endl;
            scenes_nbrframes.push_back(this->scene_from_db->value(2).toInt());
            cout<<"10"<<endl;
            QString Scene_temp = QString::number(idx, 10);
            cout<<"11"<<endl;
            Scene_temp.prepend("scene_");
            cout<<"12"<<endl;
            ui->Scene_list->addItem(Scene_temp);
            cout<<"13"<<endl;
            idx++;
            cout<<"14"<<endl;
        }else break;        
    }

}

int counted_frames;
int idx_for_cnt_frames;
int *saved_idx_for_cnt_frames;
QString *saved_token_for_cnt_frames;

//어떤 날짜에 데이터가 저장되어있는지 보고 해당 날짜의 CAM과 Lidar데이터 다운
void MainWindow::on_pushButton_clicked(){
    cout<<"push button  clicked!!\n";
//    cout<<"on_push_start"<<endl;
//    if(this_is_get_log){
//       int log_row = ui->Date_list->currentRow();
//       CurrentLog current_log = logs.at(log_row);
//       QString log_str = "Date : ";
//       log_str.append(current_log.d);
//       ui->label_7->setText(log_str);
//       selected_date=current_log.d;
//       this_is_get_log = false;
//       this->Display_Scene(current_log.t);
//       //해당 날짜 데이터 다운받는 expect script실행
//       string command="expect -f ../recv_file.exp " ;
//       command.append(selected_date.toStdString());
//       int ret=system(command.c_str());
       
//       ui->pushButton->setText("Play");
//    }else{
//       int item_row =  ui->Scene_list->currentRow();
//       QString fftoken=scenes_ftoken.at(item_row);
//       nbr_frames = scenes_nbrframes.at(item_row);
//       counted_frames = 0;
//       this->Setting_Frames(fftoken);
//    }
}


void MainWindow::on_Scene_list_itemClicked(QListWidgetItem *item){
    camWidget->clear();
    this->display_flag = true;
    this->gps_view_initialize();
    //iw->clear();
    saved_idx_for_cnt_frames = new int[200];
    saved_token_for_cnt_frames = new QString[200];
    ui->horizontalSlider->setRange(0, 200);
    ui->horizontalSlider->setValue(0);
    idx_for_cnt_frames = 0;
}



void MainWindow::Setting_Frames(QString Text){
    cout<<"setting_frames start"<<endl;
    QString current_frame_token = Text;
    this->frame_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM FRAME;";
    this->frame_from_db -> exec(selectq);

    while(display_flag){
        if(counted_frames > nbr_frames-1){
            break;
        }
        if(this->frame_from_db->next()){
            QString idx_frame_token = this->frame_from_db->value(0).toString(); //temp token
            if(idx_frame_token == current_frame_token){
                saved_idx_for_cnt_frames[counted_frames] = idx_for_cnt_frames;
                saved_token_for_cnt_frames[counted_frames] = idx_frame_token;

                ui->horizontalSlider->setValue(counted_frames);

                this->Display_Frame_Datas(current_frame_token);
                QCoreApplication::processEvents();

                current_frame_token =this->frame_from_db->value(1).toString(); //next token
                if(current_frame_token == ""){
                    display_flag=false;
                }
                counted_frames++;
            }
            idx_for_cnt_frames++;
        }
    }
    cout<<"setting_frames end"<<endl;
}

//DB에 있는 토큰값으로 플레이백
//CAM과 LiDAR는 토큰값에 해당하는 튜플에 저장된 파일명 사용
//나머지는 튜플에 저장된 센서값 사용
void MainWindow::Display_Frame_Datas(QString Text){
    //저장된 폴더 경로
    //build/YYYY-MM-DD/
    QString cur_dir="./";
    cur_dir.append(selected_date);
    
    QString pcd_dir=cur_dir+"/LIDAR/";

    QString cam_dir=cur_dir + "/CAM/";

    cout<<"display_frame_datas start"<<endl;
    QString idx_file_format;
    QString idx_frame_data_token;

    this->frame_data_jpg_from_db = new QSqlQuery(this->database);
    this->frame_data_pcd_from_db = new QSqlQuery(this->database);
    QString selectq1 = "SELECT * FROM FRAME_DATA WHERE fileformat='jpeg' and frame_token = '";
    selectq1.append(Text);
    selectq1.append("';");
    this->frame_data_jpg_from_db -> exec(selectq1);
    QString selectq2 = "SELECT * FROM FRAME_DATA WHERE fileformat='pcd' and frame_token = '";
    selectq2.append(Text);
    selectq2.append("';");
    this->frame_data_pcd_from_db -> exec(selectq2);

    this->frame_data_pcd_from_db->first();
    QString idx_lidar_filename =pcd_dir + this->frame_data_pcd_from_db->value(3).toString();
    emit send_pcd(idx_lidar_filename);
    QCoreApplication::processEvents();

    this->frame_data_jpg_from_db->first();
    QPixmap temp_jpeg;
    QString idx_jpg_filename = cam_dir+ this->frame_data_jpg_from_db->value(3).toString();
    temp_jpeg.load(idx_jpg_filename);
    camWidget->setPixmap(temp_jpeg.scaled(camWidget->width(),camWidget->height(), Qt::KeepAspectRatio));

    this->Display_Gps_Data(this->frame_data_jpg_from_db->value(1).toString());
    this->Display_Imu_Data(this->frame_data_jpg_from_db->value(1).toString());
    this->Display_Can_Data(this->frame_data_jpg_from_db->value(1).toString());

    camWidget->show();
    QCoreApplication::processEvents();
    cout<<"display frame datas end"<<endl;
}


void MainWindow::Display_Gps_Data(QString Text){
    cout<<"display gps data start"<<endl;
    QString idx_lat;
    QString idx_lng;
    double idx_hdop;
    QString idx_token;

    this->gps_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM GPS_DATA WHERE token = '";
    selectq.append(Text);
    selectq.append("';");
    this->gps_from_db -> exec(selectq);
    this->gps_from_db->first();
    idx_lat = this->gps_from_db->value(1).toString();
    idx_lng =this->gps_from_db->value(2).toString();
    idx_hdop=this->gps_from_db->value(3).toDouble();

    this->display_gps_info(idx_lat, idx_lng, idx_hdop);
    QCoreApplication::processEvents();
    cout<<"display gps data end"<<endl;
}

void MainWindow::Display_Imu_Data(QString Text){
    cout<<"display imu data start"<<endl;
//    QString idx_ax;
//    QString idx_ay;
//    QString idx_az;
    float idx_ax, idx_ay, idx_az;

    this->imu_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM IMU_DATA WHERE token = '";
    selectq.append(Text);
    selectq.append("';");
    this->imu_from_db -> exec(selectq);

    this->imu_from_db->first();
    idx_ax=this->imu_from_db->value(1).toFloat();
    idx_ay=this->imu_from_db->value(2).toFloat();
    idx_az=this->imu_from_db->value(3).toFloat();
    emit send_imu(idx_ax, idx_ay, idx_az);
//    idx_ax = this->imu_from_db->value(1).toString();
//    idx_ay =this->imu_from_db->value(2).toString();
//    idx_az =this->imu_from_db->value(3).toString();
    
//    emit send_imu(idx_ax.toFloat(), idx_ay.toFloat(), idx_az.toFloat());
    QCoreApplication::processEvents();   
    cout<<"display imu data end"<<endl;
}


void MainWindow::Display_Can_Data(QString Text){
    QString handle;
    QString speed;
    QString gear;
    QString turn;

    this->can_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM CAN_DATA WHERE token = '";
    selectq.append(Text);
    selectq.append("';");
    this->can_from_db -> exec(selectq);

    this->can_from_db->first();
    handle = this->can_from_db->value(1).toString();
    speed =this->can_from_db->value(2).toString();
    gear=this->can_from_db->value(3).toString();
    turn=this->can_from_db->value(4).toString();
    
    this->display_handle_data(handle);
    this->display_gear(gear.toInt());
    this->display_turn_indicator(turn.toInt());
    this->speedChanged(speed.toInt());
    QCoreApplication::processEvents();
}


bool MainWindow::setting_DB(){
    cout<<"setting db start"<<endl;
        // *****Set DB Information*****
        QSqlDatabase database=QSqlDatabase::addDatabase("QPSQL7");
        database.setDatabaseName("diva2");
        database.setHostName("165.246.39.124");
        database.setUserName("diva2");
        database.setPassword("1234");
        database.setPort(5432);
        bool con = false;
        if (database.open()){
            qDebug() << "Connection Successful";
            con = true;
        }
        else
            qDebug() << "Connection Failed!";

        qDebug() << "db connection" << database.open();
        return con;
}


void MainWindow::Display_Stop(){
    this->display_flag=false;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position){
    initialize_for_slider();
    idx_for_cnt_frames = saved_idx_for_cnt_frames[position];
    counted_frames = position;
    this->Setting_Frames(saved_token_for_cnt_frames[position]);
}

void MainWindow::initialize_for_slider(){
    camWidget->clear();
    this->display_flag = true;
    this->gps_view_initialize();
    //iw->clear();
}

void MainWindow::setTotal(){
    total=static_cast<double>(storage.bytesTotal()/1024/1024/1024);
    QString s_total="Total: "+QString::number(total)+" GB";
    ui->total->setText(s_total);
}

void MainWindow::setUsage(){
    total=static_cast<double>(storage.bytesTotal()/1024/1024/1024);
    QString s_total="Total: "+QString::number(total)+" GB";
    ui->total->setText(s_total);
    free=static_cast<double>(storage.bytesAvailable()/1024/1024/1024);
    QString s_free="Free: "+QString::number(free)+" GB";
    ui->usage->setText(s_free);
    used=total-free;
    percent=static_cast<int>((used/total)*100);
    //ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(percent);
}

void MainWindow::display_imu_xyz(float x, float y, float z){
    QString xs=QString::number(x);
    QString ys=QString::number(y);
    QString zs=QString::number(z);
    QString str;
    xs.prepend("Acceleration\nX: ");
    ys.prepend("G\nY: ");
    zs.prepend("G\nZ: ");
    str=xs+ys+zs+"G";
    ui->label_8->setText(str);
    QCoreApplication::processEvents();
}

void MainWindow::sensing_start(){
    system("/home/yh/real/diva2/build/MobilePlatform/Sensing/MP_sensing &");
}

void MainWindow::sensing_stop(){
    system("pkill -ef MP_sensing");
    system("expect -f ../send_file.exp 파일경로");
}
