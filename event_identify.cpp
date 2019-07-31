#include "event_identify.h"
#include <QDebug>

EventIdentify::EventIdentify()
    : is_up_(true), is_down_(false), is_move_(false)
{
    ;
}

void EventIdentify::EventUpdate(HidMtFingerReport &finger_report)
{
    qint32 x = GetX(finger_report, 0) * 1920/16384;  //coordiante tramsform
    qint32 y = GetY(finger_report, 0) * 1080/9600;

    pos_.setX(x);
    pos_.setY(y);

    if (GetTipSwitch(finger_report, 0) && is_down_) {
        is_move_ = true;
        is_up_ = false;
        is_down_ = false;
    } else if (GetTipSwitch(finger_report, 0) && is_up_) {
        is_down_ = true;
        is_up_ = false;
        is_move_ = false;
    } else if (!GetTipSwitch(finger_report, 0)) {
        is_up_ = true;
        is_move_ = false;
        is_down_ = false;
    }
}

void EventIdentify::PrintStatus()
{
    if (is_up_)
        qDebug() << "up" << endl;
    else if (is_down_)
        qDebug() << "down" << endl;
    else if (is_move_)
        qDebug() << "move" << endl;
}

bool EventIdentify::GetTipSwitch(HidMtFingerReport &finger_report, int contact_id)
{
    return finger_report.finger_rpt[contact_id].tip_switch ? true : false;
}

qint16 EventIdentify::GetX(HidMtFingerReport &finger_report, int contact_id)
{
    qint16 x_coor = 0;
    x_coor |= finger_report.finger_rpt[contact_id].x[0];
    x_coor |= (finger_report.finger_rpt[contact_id].x[1] << 8);
    return x_coor;
}

qint16 EventIdentify::GetY(HidMtFingerReport &finger_report, int contact_id)
{
    qint16 y_coor = 0;
    y_coor |= finger_report.finger_rpt[contact_id].y[0];
    y_coor |= (finger_report.finger_rpt[contact_id].y[1] << 8);
    return y_coor;
}

