#include "rawtouchevent.h"

RawTouchEvent::RawTouchEvent() //: event_type_(RawTouchEvent::RawTouchEnd)
{
    point_list_.reserve(10);
    memset(&this->finger_report, 0, sizeof(this->finger_report));
}

void RawTouchEvent::EventUpdate(HidMtFingerReport &finger_report, QRect rect)
{
    point_list_.clear();
    for (int i = 0; i < finger_report.count; ++i) {
        qint16 x = GetX(finger_report, i) * 1920/16384; //
        qint16 y = GetY(finger_report, i) * 996/9600;   //
        x = x - rect.x();
        y = y - rect.y();

        if (GetTipSwitch(finger_report, i)) {  //down or move
            if (map_.count(finger_report.finger_rpt[i].contact_id) != 0) { //has record
                if (map_[finger_report.finger_rpt[i].contact_id] == Qt::TouchPointPressed)
                    map_[finger_report.finger_rpt[i].contact_id] = Qt::TouchPointMoved;
                else if (map_[finger_report.finger_rpt[i].contact_id] == Qt::TouchPointReleased)
                    map_[finger_report.finger_rpt[i].contact_id] = Qt::TouchPointPressed;
            } else { // has no record
                map_.insert(finger_report.finger_rpt[i].contact_id, Qt::TouchPointPressed);
            }
        } else { //up
            map_[finger_report.finger_rpt[i].contact_id] = Qt::TouchPointReleased;
        }
        TouchPoint point(finger_report.finger_rpt[i].contact_id, map_[i], QPointF(x, y));
        point_list_.push_back(point);
    }
}

bool RawTouchEvent::IsTouchUpdate(HidMtFingerReport &finger_report)
{
    if (this->finger_report.count != finger_report.count)
        return true;
    else {
        for (int i = 0; i < this->finger_report.count; ++i) {
            if (GetTipSwitch(this->finger_report, i) !=
                    GetTipSwitch(finger_report, i))
                return true;
            if (GetX(this->finger_report, i) !=
                    GetX(finger_report, i))
                return true;
            if (GetY(this->finger_report, i) !=
                    GetY(finger_report, i))
                return true;
        }
        return false;
    }
}

bool RawTouchEvent::GetTipSwitch(HidMtFingerReport &finger_report, int index)
{
    return finger_report.finger_rpt[index].tip_switch ? true : false;
}

qint16 RawTouchEvent::GetX(HidMtFingerReport &finger_report, int index)
{
    qint16 x_coor = 0;
    x_coor |= finger_report.finger_rpt[index].x[0];
    x_coor |= (finger_report.finger_rpt[index].x[1] << 8);
    return x_coor;
}

qint16 RawTouchEvent::GetY(HidMtFingerReport &finger_report, int index)
{
    qint16 y_coor = 0;
    y_coor |= finger_report.finger_rpt[index].y[0];
    y_coor |= (finger_report.finger_rpt[index].y[1] << 8);
    return y_coor;
}



RawTouchEvent::TouchPoint::TouchPoint(int id, Qt::TouchPointState state, QPointF pos):
    touch_id_(id), touch_state_(state), touch_pos_(pos)
{
    ;
}

RawTouchEvent::TouchPoint::~TouchPoint()
{
    ;
}
