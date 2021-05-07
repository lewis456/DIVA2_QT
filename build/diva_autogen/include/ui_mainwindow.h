/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLive_Streaming;
    QAction *actionGet_Log;
    QAction *actionStreaming_End;
    QAction *actionInitializing;
    QAction *actionIntializing;
    QAction *actionInitializing_2;
    QAction *actionStroing_To_DB;
    QAction *actionFinish;
    QAction *actionTest;
    QAction *actionJSON_Parsing;
    QAction *actionDB_Storing;
    QWidget *centralwidget;
    QLabel *label_5;
    QLabel *label_7;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *P_label;
    QLabel *R_label;
    QLabel *N_label;
    QLabel *D_label;
    QLabel *label;
    QLabel *label_2;
    QLabel *total;
    QLabel *usage;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_4;
    QLabel *label_10;
    QProgressBar *progressBar;
    QCheckBox *gps_cb;
    QCheckBox *imu_cb;
    QCheckBox *can_cb;
    QCheckBox *cam_cb;
    QCheckBox *lidar_cb;
    QLabel *Cam;
    QLabel *signal1;
    QLabel *signal2;
    QLabel *signal3;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QMenu *menuStreaming;
    QMenu *menuPlayback;
    QMenu *menuData_Processing;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1776, 900);
        MainWindow->setStyleSheet(QString::fromUtf8("background : rgb(211, 215, 207)"));
        actionLive_Streaming = new QAction(MainWindow);
        actionLive_Streaming->setObjectName(QString::fromUtf8("actionLive_Streaming"));
        actionGet_Log = new QAction(MainWindow);
        actionGet_Log->setObjectName(QString::fromUtf8("actionGet_Log"));
        actionStreaming_End = new QAction(MainWindow);
        actionStreaming_End->setObjectName(QString::fromUtf8("actionStreaming_End"));
        actionInitializing = new QAction(MainWindow);
        actionInitializing->setObjectName(QString::fromUtf8("actionInitializing"));
        actionIntializing = new QAction(MainWindow);
        actionIntializing->setObjectName(QString::fromUtf8("actionIntializing"));
        actionInitializing_2 = new QAction(MainWindow);
        actionInitializing_2->setObjectName(QString::fromUtf8("actionInitializing_2"));
        actionStroing_To_DB = new QAction(MainWindow);
        actionStroing_To_DB->setObjectName(QString::fromUtf8("actionStroing_To_DB"));
        actionFinish = new QAction(MainWindow);
        actionFinish->setObjectName(QString::fromUtf8("actionFinish"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QString::fromUtf8("actionTest"));
        actionJSON_Parsing = new QAction(MainWindow);
        actionJSON_Parsing->setObjectName(QString::fromUtf8("actionJSON_Parsing"));
        actionDB_Storing = new QAction(MainWindow);
        actionDB_Storing->setObjectName(QString::fromUtf8("actionDB_Storing"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1240, 340, 311, 111));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,80);\n"
""));
        label_5->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1570, 20, 201, 41));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,80);\n"
"color: rgb(98, 114, 164);"));
        label_7->setAlignment(Qt::AlignCenter);
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(1240, 830, 531, 41));
        horizontalSlider->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);\n"
"background-color: rgba(238, 238, 236, 180);"));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1570, 790, 201, 31));
        pushButton->setStyleSheet(QString::fromUtf8("background : rgb(114, 159, 207)"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(1240, 10, 311, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 450, 621, 421));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(1240, 470, 311, 261));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        P_label = new QLabel(centralwidget);
        P_label->setObjectName(QString::fromUtf8("P_label"));
        P_label->setGeometry(QRect(1300, 220, 50, 40));
        P_label->setStyleSheet(QString::fromUtf8("font: 75 30pt \"Ubuntu Mono\";\n"
"color: rgb(40, 42, 54);\n"
"background-color: rgba(255, 255, 255,0);psql -h localhost -p 5432 -U diva -d \"diva\""));
        P_label->setAlignment(Qt::AlignCenter);
        R_label = new QLabel(centralwidget);
        R_label->setObjectName(QString::fromUtf8("R_label"));
        R_label->setGeometry(QRect(1350, 220, 50, 40));
        R_label->setStyleSheet(QString::fromUtf8("font: 75 30pt \"Ubuntu Mono\";\n"
"color: rgb(40, 42, 54);\n"
"background-color: rgba(255, 255, 255,0);psql -h localhost -p 5432 -U diva -d \"diva\""));
        R_label->setAlignment(Qt::AlignCenter);
        N_label = new QLabel(centralwidget);
        N_label->setObjectName(QString::fromUtf8("N_label"));
        N_label->setGeometry(QRect(1400, 220, 50, 40));
        N_label->setStyleSheet(QString::fromUtf8("font: 75 30pt \"Ubuntu Mono\";\n"
"color: rgb(40, 42, 54);\n"
"background-color: rgba(255, 255, 255,0);psql -h localhost -p 5432 -U diva -d \"diva\""));
        N_label->setAlignment(Qt::AlignCenter);
        D_label = new QLabel(centralwidget);
        D_label->setObjectName(QString::fromUtf8("D_label"));
        D_label->setGeometry(QRect(1450, 220, 50, 40));
        D_label->setStyleSheet(QString::fromUtf8("font: 75 30pt \"Ubuntu Mono\";\n"
"color: rgb(40, 42, 54);\n"
"background-color: rgba(255, 255, 255,0);psql -h localhost -p 5432 -U diva -d \"diva\""));
        D_label->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1420, 260, 80, 80));
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,0)"));
        label->setPixmap(QPixmap(QString::fromUtf8("rightarrowbefore.png")));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1300, 260, 80, 80));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,0)"));
        label_2->setPixmap(QPixmap(QString::fromUtf8("leftarrowbefore.png")));
        total = new QLabel(centralwidget);
        total->setObjectName(QString::fromUtf8("total"));
        total->setGeometry(QRect(1580, 100, 181, 32));
        total->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,0);"));
        usage = new QLabel(centralwidget);
        usage->setObjectName(QString::fromUtf8("usage"));
        usage->setGeometry(QRect(1580, 130, 181, 31));
        usage->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,0);\n"
""));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(1240, 750, 311, 71));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,80);\n"
""));
        label_8->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1570, 230, 201, 221));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,80);\n"
""));
        label_6->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(1570, 80, 201, 131));
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,80);\n"
"color: rgb(98, 114, 164);"));
        label_9->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1620, 220, 111, 20));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,0);"));
        label_4->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(1620, 70, 111, 20));
        label_10->setFont(font);
        label_10->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,0);"));
        label_10->setAlignment(Qt::AlignCenter);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(1580, 170, 181, 31));
        QFont font1;
        font1.setBold(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        progressBar->setFont(font1);
        progressBar->setAutoFillBackground(false);
        progressBar->setValue(0);
        gps_cb = new QCheckBox(centralwidget);
        gps_cb->setObjectName(QString::fromUtf8("gps_cb"));
        gps_cb->setGeometry(QRect(1591, 257, 51, 23));
        gps_cb->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);"));
        gps_cb->setChecked(true);
        imu_cb = new QCheckBox(centralwidget);
        imu_cb->setObjectName(QString::fromUtf8("imu_cb"));
        imu_cb->setGeometry(QRect(1591, 292, 53, 23));
        imu_cb->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);"));
        imu_cb->setChecked(true);
        can_cb = new QCheckBox(centralwidget);
        can_cb->setObjectName(QString::fromUtf8("can_cb"));
        can_cb->setGeometry(QRect(1591, 327, 56, 23));
        can_cb->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);"));
        can_cb->setChecked(true);
        cam_cb = new QCheckBox(centralwidget);
        cam_cb->setObjectName(QString::fromUtf8("cam_cb"));
        cam_cb->setGeometry(QRect(1591, 362, 58, 23));
        cam_cb->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);"));
        cam_cb->setChecked(true);
        lidar_cb = new QCheckBox(centralwidget);
        lidar_cb->setObjectName(QString::fromUtf8("lidar_cb"));
        lidar_cb->setGeometry(QRect(1591, 397, 68, 23));
        lidar_cb->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);"));
        lidar_cb->setChecked(true);
        Cam = new QLabel(centralwidget);
        Cam->setObjectName(QString::fromUtf8("Cam"));
        Cam->setGeometry(QRect(10, 10, 621, 431));
        Cam->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,80);\n"
""));
        signal1 = new QLabel(centralwidget);
        signal1->setObjectName(QString::fromUtf8("signal1"));
        signal1->setGeometry(QRect(690, 845, 10, 15));
        signal1->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,0);\n"
"border-radius: 5px;"));
        signal2 = new QLabel(centralwidget);
        signal2->setObjectName(QString::fromUtf8("signal2"));
        signal2->setGeometry(QRect(700, 840, 10, 20));
        signal2->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,0);\n"
"border-radius: 5px;"));
        signal3 = new QLabel(centralwidget);
        signal3->setObjectName(QString::fromUtf8("signal3"));
        signal3->setGeometry(QRect(710, 830, 10, 30));
        signal3->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,0);\n"
"border-radius: 5px;"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(1570, 470, 201, 311));
        MainWindow->setCentralWidget(centralwidget);
        label_6->raise();
        gps_cb->raise();
        imu_cb->raise();
        can_cb->raise();
        cam_cb->raise();
        lidar_cb->raise();
        label_9->raise();
        label_5->raise();
        label_7->raise();
        horizontalSlider->raise();
        pushButton->raise();
        gridLayoutWidget->raise();
        gridLayoutWidget_2->raise();
        gridLayoutWidget_3->raise();
        P_label->raise();
        R_label->raise();
        N_label->raise();
        D_label->raise();
        label->raise();
        label_2->raise();
        total->raise();
        usage->raise();
        label_8->raise();
        label_4->raise();
        label_10->raise();
        progressBar->raise();
        Cam->raise();
        signal1->raise();
        signal2->raise();
        signal3->raise();
        listWidget->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1776, 22));
        menubar->setStyleSheet(QString::fromUtf8("background-color: rgba(238, 238, 236, 200);\n"
"color: rgba(103, 73, 203, 230);"));
        menuStreaming = new QMenu(menubar);
        menuStreaming->setObjectName(QString::fromUtf8("menuStreaming"));
        menuStreaming->setStyleSheet(QString::fromUtf8(""));
        menuPlayback = new QMenu(menubar);
        menuPlayback->setObjectName(QString::fromUtf8("menuPlayback"));
        menuData_Processing = new QMenu(menubar);
        menuData_Processing->setObjectName(QString::fromUtf8("menuData_Processing"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuStreaming->menuAction());
        menubar->addAction(menuData_Processing->menuAction());
        menubar->addAction(menuPlayback->menuAction());
        menuStreaming->addAction(actionInitializing);
        menuStreaming->addAction(actionLive_Streaming);
        menuStreaming->addAction(actionStreaming_End);
        menuPlayback->addAction(actionInitializing_2);
        menuPlayback->addAction(actionGet_Log);
        menuPlayback->addAction(actionFinish);
        menuData_Processing->addAction(actionJSON_Parsing);
        menuData_Processing->addAction(actionDB_Storing);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DIVA _ Data Intergration for Vehicle Assistance", nullptr));
        actionLive_Streaming->setText(QApplication::translate("MainWindow", "Live Streaming", nullptr));
        actionGet_Log->setText(QApplication::translate("MainWindow", "Get Log", nullptr));
        actionStreaming_End->setText(QApplication::translate("MainWindow", "Streaming End", nullptr));
        actionInitializing->setText(QApplication::translate("MainWindow", "Initializing", nullptr));
        actionIntializing->setText(QApplication::translate("MainWindow", "Intializing", nullptr));
        actionInitializing_2->setText(QApplication::translate("MainWindow", "Initializing", nullptr));
        actionStroing_To_DB->setText(QApplication::translate("MainWindow", "Stroing To DB", nullptr));
        actionFinish->setText(QApplication::translate("MainWindow", "Finish", nullptr));
        actionTest->setText(QApplication::translate("MainWindow", "Test", nullptr));
        actionJSON_Parsing->setText(QApplication::translate("MainWindow", "JSON Parsing", nullptr));
        actionDB_Storing->setText(QApplication::translate("MainWindow", "DB Storing", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Handle Data", nullptr));
        label_7->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "Start Play", nullptr));
        P_label->setText(QApplication::translate("MainWindow", "P", nullptr));
        R_label->setText(QApplication::translate("MainWindow", "R", nullptr));
        N_label->setText(QApplication::translate("MainWindow", "N", nullptr));
        D_label->setText(QApplication::translate("MainWindow", "D", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        total->setText(QApplication::translate("MainWindow", "Total: ", nullptr));
        usage->setText(QApplication::translate("MainWindow", "Free: ", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Accel X,Y,Z", nullptr));
        label_6->setText(QString());
        label_9->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Data Setting", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Memory", nullptr));
        gps_cb->setText(QApplication::translate("MainWindow", "GPS", nullptr));
        imu_cb->setText(QApplication::translate("MainWindow", "IMU", nullptr));
        can_cb->setText(QApplication::translate("MainWindow", "CAN", nullptr));
        cam_cb->setText(QApplication::translate("MainWindow", "CAM", nullptr));
        lidar_cb->setText(QApplication::translate("MainWindow", "LiDAR", nullptr));
        Cam->setText(QString());
        signal1->setText(QString());
        signal2->setText(QString());
        signal3->setText(QString());
        menuStreaming->setTitle(QApplication::translate("MainWindow", "Streaming", nullptr));
        menuPlayback->setTitle(QString());
        menuData_Processing->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
