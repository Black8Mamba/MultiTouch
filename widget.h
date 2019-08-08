#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>
#include "thread.h"
#include "raw_touch_event.h"

namespace Ui {
class Widget;
}

class Slide;
class Widget : public QGraphicsView
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void SetInkColor(const QColor color);
    void SetInkThickness(int thickness);

    Slide* CurrentSlide(void) const { return this->current_slide_; }
    void SetScene(Slide *scene);

protected:
    void resizeEvent(QResizeEvent *event);
    virtual bool viewportEvent(QEvent *event);

private slots:
    void UpdateDataSlot(HidMtFingerReport *finger_report);
    void HandleTimeOut(void);

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_thickness_currentIndexChanged(int index);

    void on_GraphicsType_currentIndexChanged(int index);

private:
    void InitTimerMap();
    void DeleteTimerMap();

private:
    Slide *current_slide_;
    int data_source_;

    MyThread thread_;
    RawTouchEvent event_;
    QTimer timer_;
    QMap<int, QTimer*> timer_map_;
    Ui::Widget *ui;
};

#endif // WIDGET_H
