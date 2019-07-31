#include "widget.h"
#include "slide.h"

#include <QTouchEvent>
#include <QEvent>

Widget::Widget(QWidget *parent):
    QGraphicsView(parent)
{
    this->setInteractive(true);
    this->setOptimizationFlag(QGraphicsView::IndirectPainting);
    this->setCacheMode(QGraphicsView::CacheBackground);

    this->setAttribute(Qt::WA_AcceptTouchEvents);
    this->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

    setRenderHint(QPainter::Antialiasing, true);

    Slide *slide = new Slide;
    this->setScene(slide);
    this->setSceneRect(0, 0, 600, 600);
    this->resize(600, 600);

    slide->SetColor(Qt::black);//color
    slide->SetThickness(5); //line width

    this->current_slide_ = slide;
}

Widget::~Widget()
{

}

void Widget::SetScene(Slide *scene)
{
    Q_EMIT SlideChangedBefore();
    QGraphicsView::setScene(scene);
    this->current_slide_ = scene;
    Q_EMIT SlideChangedAfter();
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    this->setSceneRect(0, 0, this->width(), this->height());
    this->centerOn(this->width()/2, this->height()/2);
}

bool Widget::viewportEvent(QEvent *event)
{
    QEvent::Type ev_type = event->type();
    if (ev_type == QEvent::TouchBegin || ev_type == QEvent::TouchUpdate
            ||ev_type == QEvent::TouchEnd) {
        QTouchEvent *touch_event = static_cast<QTouchEvent*>(event);
        QList<QTouchEvent::TouchPoint> touch_points = touch_event->touchPoints();
        foreach (const QTouchEvent::TouchPoint tp, touch_points) {
           QPoint touchPos = QPoint(tp.pos().x(), tp.pos().y());
           if (tp.id() == 0) {
               if (tp.state() == Qt::TouchPointPressed)
                   this->is_touch_mode_ = true;
               else
                   this->is_touch_mode_ = false;
           }

           QPointF scene_pos = this->mapToScene(touchPos.x(), touchPos.y());
           switch(tp.state()) {
           case Qt::TouchPointPressed:
               this->current_slide_->OnDeviceDown(scene_pos, tp.id());
               break;
           case Qt::TouchPointMoved:
               this->current_slide_->OnDeviceMove(scene_pos, tp.id());
               break;
           case Qt::TouchPointReleased:
               this->current_slide_->OnDeviceUp(scene_pos, tp.id());
               break;
           default:
               break;
           }
        }

        if (ev_type == QEvent::TouchEnd) {
            ;
        }
        return true;
    }
    return QGraphicsView::viewportEvent(event);
}




