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
    HidMtFingerReport finger_report_;
    int fd_;
signals:
    void UpdateDataSignal(HidMtFingerReport finger_report);
};

#endif // MYTHREAD_H
