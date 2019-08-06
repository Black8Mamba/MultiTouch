#include "mythread.h"
#include <QDebug>
#include <cstring>
#include <QSettings>

MyThread::MyThread()
{
    stopped_ = false;
    fd_ = 0;
    fd_data_ = 0;
    QSettings configIni("para.ini", QSettings::IniFormat);
    path_ =  configIni.value("DataFilePath/Path").toString();
    data_source_ = configIni.value("Setting/DataSource").toInt();

    memset(&finger_report_, 0, sizeof(finger_report_));
    string device_node = device::GetDeviceNode("/dev/", "input0");
    if (device_node.size() == 0) {
        qDebug() << "get device failed" << endl;
        exit(-1);
    }

    if (data_source_ == 1) {
        fd_ = open(device_node.c_str(), O_RDONLY);
        if (fd_ < 0) {
            qDebug() << "open device failed" << endl;
            exit(-1);
        }
        qDebug() << "fd is " << fd_ << endl;
    }

    if (data_source_ == 2) {
        fd_data_ = open(path_.toStdString().c_str(), O_RDWR);
        if (fd_data_ < 0) {
            qDebug() << "open datafile failed" << endl;
            exit(-1);
        }
    }
}
MyThread::~MyThread()
{
    close(fd_);
    close(fd_data_);
}

void MyThread:: run()
{
    stopped_ = false;

    while(!stopped_) {
        if (data_source_ == 1) {
            if (TouchDataReceive(fd_, reinterpret_cast<unsigned char*>(&finger_report_), sizeof(finger_report_)) == 0)
                break;
              //TouchDataSend(fd_data_, reinterpret_cast<unsigned char*>(&finger_report_), sizeof(finger_report_));
        } else if (data_source_ == 2) {
            qDebug() << "2" << endl;
            if (TouchDataReceive(fd_data_, reinterpret_cast<unsigned char*>(&finger_report_), sizeof(finger_report_)) == 0)
                break;
        }
        emit UpdateDataSignal(&finger_report_);
        if (data_source_ == 2)
            msleep(20);
    }
    stopped_ = false;
}

void MyThread::stop()
{
    stopped_ = true;
    qDebug() << "thread exit:" << endl;
}
