#ifndef RAWTOUCHEVENT_H
#define RAWTOUCHEVENT_H

#include <QObject>
#include <QList>
#include "touch_data_receive.h"

class RawTouchEvent
{
    //enum Type{
    //    RawTouchBegin = 1,
    //    RawTouchUpdate = 2,
    //    RawTouchEnd = 3,
    //};
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
    bool IsTouchStart(HidMtFingerReport& finger_report);
    bool IsTouchEnd(HidMtFingerReport& finger_report);
    QList<RawTouchEvent::TouchPoint>* touchPoints() { return &point_list_; }
   // RawTouchEvent::Type type() const { return event_type_; }
    void SetFingerReport(HidMtFingerReport &finger_report) { this->finger_report = finger_report; }

private:
    bool GetTipSwitch(HidMtFingerReport& finger_report, int index);
    qint16 GetX(HidMtFingerReport& finger_report, int index);
    qint16 GetY(HidMtFingerReport& finger_report, int index);

private:
    QList<RawTouchEvent::TouchPoint> point_list_;
    HidMtFingerReport finger_report;
    //RawTouchEvent::Type event_type_;
    QMap<int, Qt::TouchPointState> map_;
};

#endif // RAWTOUCHEVENT_H
