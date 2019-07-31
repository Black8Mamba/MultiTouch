#ifndef EVENT_IDENTIFY_H
#define EVENT_IDENTIFY_H

#include "touch_data_receive.h"
#include <QPoint>


//class event_identify
class EventIdentify
{
public:
    EventIdentify();
    //void event_update(HidMtFingerReport& finger_report);
    void EventUpdate(HidMtFingerReport& finger_report);
    //void printStatus();
    void PrintStatus();

public:
    bool GetTipSwitch(HidMtFingerReport& finger_report, int contact_id);
    qint16 GetX(HidMtFingerReport& finger_report, int contact_id);
    qint16 GetY(HidMtFingerReport& finger_report, int contact_id);

    bool GetUp() {  return is_up_; }
    bool GetMove() { return is_move_; }
    bool GetDown() { return is_down_; }
    QPoint GetPos() { return pos_; }

private:
    bool is_up_;
    bool is_down_;
    bool is_move_;

    QPoint pos_;
};

#endif // EVENT_IDENTIFY_H
