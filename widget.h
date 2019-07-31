#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>

class Slide;
class Widget : public QGraphicsView
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void SetInkColor(const QColor *color);
    void SetInkThickness(int thickness);

    Slide* CurrentSlide(void) const {return this->current_slide_; }
    void SetScene(Slide *scene);

protected:
    void resizeEvent(QResizeEvent *event);
    virtual bool viewportEvent(QEvent *event);

private:
    Slide *current_slide_;
    bool is_touch_mode_;

signals:
    void SlideChangedBefore(void);
    void SlideChangedAfter(void);
};

#endif // WIDGET_H