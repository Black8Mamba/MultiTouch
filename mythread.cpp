#include "mythread.h"
#include <QDebug>
#include <cstring>

MyThread::MyThread()
{
    stopped_ = false;
    fd_ = 0;
    memset(&finger_report_, 0, sizeof(finger_report_));
    string device_node = device::GetDeviceNode("/dev/", "input0");
    if (device_node.size() == 0) {
        qDebug() << "get device failed" << endl;
        exit(-1);
    }
    fd_ = open(device_node.c_str(), O_RDONLY);
    if (fd_ < 0) {
        qDebug() << "open device failed" << endl;
        exit(-1);
    }
    qDebug() << "fd is " << fd_ << endl;
    qRegisterMetaType<HidMtFingerReport>("HidMfFingerReport");
}
MyThread::~MyThread()
{
    close(fd_);
}

void MyThread:: run()
{
    qDebug() << "thread start:" << endl;
    stopped_ = false;
    while(!stopped_) {
        TouchDataReceive(fd_, reinterpret_cast<unsigned char*>(&finger_report_), sizeof(finger_report_));
       // qDebug() << "thead!" << endl;
        emit UpdateDataSignal(&finger_report_);
    }
    stopped_ = false;
}

void MyThread::stop()
{
    stopped_ = true;
    qDebug() << "thread exit:" << endl;
}
