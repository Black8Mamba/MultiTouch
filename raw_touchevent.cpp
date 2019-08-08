#include "raw_touch_event.h"
#include <QDebug>


RawTouchEvent::RawTouchEvent()
{
    point_list_.reserve(10);
    this->finger_report_ = NULL;
}

void RawTouchEvent::EventUpdate(HidMtFingerReport &finger_report, QRect rect)
{
    point_list_.clear();
    for (int i = 0; i < finger_report.count; ++i) {
        qint16 x = GetX(finger_report, i) * CVT_DEV_TOUCH_WINDOWS_WIDTH / CVT_DEF_TOUCH_DEV_WIDTH; //
        qint16 y = GetY(finger_report, i) * CVT_DEV_TOUCH_WINDOWS_HEIGHT / CVT_DEF_TOUCH_DEV_HEIGHT;   //
        x = x - rect.x();
        y = y - rect.y();

        if (GetTipSwitch(finger_report, i)) {  //down or move
            if (map_.count(finger_report.finger_rpt[i].contact_id) != 0) { //have record
                if (map_[finger_report.finger_rpt[i].contact_id] == Qt::TouchPointPressed)
                    map_[finger_report.finger_rpt[i].contact_id] = Qt::TouchPointMoved;
                else if (map_[finger_report.finger_rpt[i].contact_id] == Qt::TouchPointReleased)
                    map_[finger_report.finger_rpt[i].contact_id] = Qt::TouchPointPressed;
            } else { // have no record
                map_.insert(finger_report.finger_rpt[i].contact_id, Qt::TouchPointPressed);
            }
        } else { //up
            map_[finger_report.finger_rpt[i].contact_id] = Qt::TouchPointReleased;
        }

        TouchPoint point(finger_report.finger_rpt[i].contact_id,
                         map_[finger_report.finger_rpt[i].contact_id],
                            QPointF(x, y));
        point_list_.push_back(point);
    }
}

bool RawTouchEvent::IsTouchUpdate(HidMtFingerReport &finger_report)
{
    if (this->finger_report_ == NULL)
        return true;

    if (this->finger_report_->count != finger_report.count)
        return true;
    else {
        for (int i = 0; i < this->finger_report_->count; ++i) {
            if (GetTipSwitch(*(this->finger_report_), i) !=
                    GetTipSwitch(finger_report, i))
                return true;
            if (GetX(*(this->finger_report_), i) !=
                    GetX(finger_report, i))
                return true;
            if (GetY(*(this->finger_report_), i) !=
                    GetY(finger_report, i))
                return true;
        }
        return false;
    }
}

bool RawTouchEvent::IsTouchEnd(HidMtFingerReport &finger_report)
{
    for (int i = 0; i < finger_report.count; ++i) {
        if (finger_report.finger_rpt[i].tip_switch)
            return false;
    }
    return true;
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
