#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include "mythread.h"
#include "rawtouchevent.h"
#include <QTimer>

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

    Slide* CurrentSlide(void) const {return this->current_slide_; }
    void SetScene(Slide *scene);

protected:
    void resizeEvent(QResizeEvent *event);
    virtual bool viewportEvent(QEvent *event);
    //void timerEvent(QTimerEvent *event);

private slots:
    void UpdateDataSlot(HidMtFingerReport *finger_report);
    void HandleTimeOut(void);

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_thickness_currentIndexChanged(int index);

private:
    void InitTimerMap();
    void DeleteTimerMap();

private:
    Slide *current_slide_;
    bool is_touch_mode_;
    int data_source_;

    MyThread thread_;
    RawTouchEvent event_;
    QTimer timer_;
    QMap<int, QTimer*> timer_map_;
    Ui::Widget *ui;

signals:
    void SlideChangedBefore(void);
    void SlideChangedAfter(void);
};

#endif // WIDGET_H
