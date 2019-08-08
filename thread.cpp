#include "thread.h"
#include <QDebug>
#include <cstring>
#include <QSettings>
#include <cstdlib>

MyThread::MyThread()
{
    stopped_ = false;
    fd_dev_ = 0;
    fd_data_ = 0;
    QSettings configIni(CVT_DEF_CONFIG_FILE_PATH, QSettings::IniFormat);
    path_ =  configIni.value("DataFilePath/Path").toString();
    data_source_ = configIni.value("Setting/DataSource").toInt();

    string device_node = device::GetDeviceNode(CVT_DEF_HID_DEV_PATH, CVT_DEF_HID_PHY_INFO);
    if (device_node.size() == 0) {
        qDebug() << "get device failed" << endl;
        exit(-1);
    }

    if (data_source_ == RAW_DATA) {
        fd_dev_ = open(device_node.c_str(), O_RDONLY);
        if (fd_dev_ < 0) {
            qDebug() << "open device failed" << endl;
            exit(-1);
        }
    }

    if (data_source_ == DATA_FILE) {
        fd_data_ = open(path_.toStdString().c_str(), O_RDWR);
        if (fd_data_ < 0) {
            qDebug() << "open datafile failed" << endl;
            exit(-1);
        }
    }
}
MyThread::~MyThread()
{
    close(fd_dev_);
    close(fd_data_);
}

void MyThread:: run()
{
    stopped_ = false;
    while(!stopped_) {
        HidMtFingerReport *finger_report_ = reinterpret_cast<HidMtFingerReport*>(malloc(sizeof(HidMtFingerReport)));
        if (data_source_ == RAW_DATA) {
            if (TouchDataReceive(fd_dev_, reinterpret_cast<unsigned char*>(finger_report_), sizeof(HidMtFingerReport)) == 0)
                break;
        } else if (data_source_ == DATA_FILE) {
            if (TouchDataReceive(fd_data_, reinterpret_cast<unsigned char*>(finger_report_), sizeof(HidMtFingerReport)) == 0)
                break;
        }
        emit UpdateDataSignal(finger_report_);
        if (data_source_ == DATA_FILE)
            msleep(20);
    }
    stopped_ = false;
}

void MyThread::stop()
{
    stopped_ = true;
}
