#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include "touch_data_receive.h"
#include "device_node_identify.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QMetaType>

#define CVT_DEF_CONFIG_FILE_PATH     "./para.ini"
#define CVT_DEF_HID_DEV_PATH        "/dev/"
#define CVT_DEF_HID_PHY_INFO        "input0"

namespace  {
enum DataSource{
    INPUT_EVENT = 0,
    RAW_DATA = 1,
    DATA_FILE = 2
};
}


class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
    ~MyThread();
    void stop();

protected:
    void run();

private:
    volatile bool stopped_;
    int fd_dev_;
    int fd_data_;
    QString path_;
    int data_source_;

signals:
    void UpdateDataSignal(HidMtFingerReport* finger_report);
};

#endif // MYTHREAD_H
