/*
 * @Description: In User Settings Edit
 * @Author: Yongjie
 * @Date: 2019-09-06 14:42:29
 * @LastEditTime: 2019-09-06 20:17:27
 * @LastEditors: Please set LastEditors
 */
#ifndef RAWTOUCHEVENT_H
#define RAWTOUCHEVENT_H

#include <QObject>
#include <QList>
#include "touch_data_receive.h"

#define CVT_DEF_TOUCH_DEV_WIDTH         16384
#define CVT_DEF_TOUCH_DEV_HEIGHT        9600

#define CVT_DEV_TOUCH_WINDOWS_WIDTH     1920
#define CVT_DEV_TOUCH_WINDOWS_HEIGHT    996


class RawTouchEvent
{
public:
    class TouchPoint {
    public:

        TouchPoint(int id = -1, Qt::TouchPointState state = Qt::TouchPointReleased, QPointF pos = QPointF(0, 0));
        ~TouchPoint();

        int id(void) const {return touch_id_; }
        Qt::TouchPointState state() const { return touch_state_; }
        QPointF pos() const { return touch_pos_; }

    private:
        int touch_id_;
        Qt::TouchPointState touch_state_;
        QPointF touch_pos_;
    };

public:

    RawTouchEvent();
    void EventUpdate(HidMtFingerReport& finger_report, QRect rect);
    bool IsTouchUpdate(HidMtFingerReport& finger_report);
    bool IsTouchEnd(HidMtFingerReport& finger_report);
    QList<RawTouchEvent::TouchPoint>* touchPoints() { return &point_list_; }
    HidMtFingerReport* GetHidFingerReport() { return finger_report_; }

    void SetFingerReport(HidMtFingerReport *finger_report)
    {
        if (this->finger_report_)
            free(this->finger_report_);
        this->finger_report_ = finger_report;
    }

private:
    //raw数据解析
    bool GetTipSwitch(HidMtFingerReport& finger_report, int index);
    qint16 GetX(HidMtFingerReport& finger_report, int index);
    qint16 GetY(HidMtFingerReport& finger_report, int index);

private:
    QList<RawTouchEvent::TouchPoint> point_list_; //触点list
    HidMtFingerReport *finger_report_; //触控raw数据
    QMap<int, Qt::TouchPointState> map_; //<触点id，触点状态>,用于保存每个触点的状态
};

#endif // RAWTOUCHEVENT_H
