#include "widget.h"
#include "slide.h"
#include "ui_widget.h"
#include <QSettings>
#include <QPushButton>
#include <QTouchEvent>
#include <QEvent>
#include <QDebug>
#include <QPushButton>
#include <QMenu>

Widget::Widget(QWidget *parent):
    QGraphicsView(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    InitTimerMap();

    this->setInteractive(true);
    this->setOptimizationFlag(QGraphicsView::IndirectPainting);
    this->setCacheMode(QGraphicsView::CacheBackground);

    this->setAttribute(Qt::WA_AcceptTouchEvents);
    this->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

    setRenderHint(QPainter::Antialiasing, true);

    Slide *slide = new Slide;
    this->setScene(slide);
    this->setSceneRect(0, 0, 1300, 1000);
    this->resize(1300, 1000);

    slide->SetColor(Qt::black);//color
    slide->SetThickness(3); //line width

    this->current_slide_ = slide;

    QSettings *configIni = new QSettings("para.ini", QSettings::IniFormat);
    data_source_ = configIni->value("Setting/DataSource").toInt();

    //0:inputEvent
    //1:Raw
    qDebug() << "DataSource" << data_source_ << endl;

    this->current_slide_->SetTouchMode(false);

     qRegisterMetaType<HidMtFingerReport*>("HidMtFingerReport*");
     connect(&thread_, SIGNAL(UpdateDataSignal(HidMtFingerReport*)),
                this, SLOT(UpdateDataSlot(HidMtFingerReport*)));
     if (data_source_ == 1)
        thread_.start();
}

Widget::~Widget()
{
    if (data_source_ == 1)
        thread_.stop();
    timer_.stop();
    DeleteTimerMap();
}

void Widget::SetInkColor(const QColor color)
{
    this->current_slide_->SetColor(color);
}

void Widget::SetInkThickness(int thickness)
{
    this->current_slide_->SetThickness(thickness);
}

void Widget::SetScene(Slide *scene)
{
    QGraphicsView::setScene(scene);
    this->current_slide_ = scene;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    this->setSceneRect(0, 0, this->width(), this->height());
    this->centerOn(this->width()/2, this->height()/2);
}

bool Widget::viewportEvent(QEvent *event)
{
    if (data_source_ == 0) {
        QEvent::Type ev_type = event->type();
        if (ev_type == QEvent::TouchBegin || ev_type == QEvent::TouchUpdate
                ||ev_type == QEvent::TouchEnd) {
            QTouchEvent *touch_event = static_cast<QTouchEvent*>(event);
            QList<QTouchEvent::TouchPoint> touch_points = touch_event->touchPoints();
            if (ev_type == QEvent::TouchBegin) {
                this->is_touch_mode_ = true;
                this->current_slide_->SetTouchMode(true);;
            } else if (ev_type == QEvent::TouchEnd) {
                this->is_touch_mode_ = false;
                this->current_slide_->SetTouchMode(false);
            }

            foreach (const QTouchEvent::TouchPoint tp, touch_points) {
               QPoint touchPos = QPoint(tp.pos().x(), tp.pos().y());
               qDebug() << touchPos << endl;

               QPointF scene_pos = this->mapToScene(touchPos.x(), touchPos.y());
               switch(tp.state()) {
               case Qt::TouchPointPressed:
                   this->current_slide_->OnDeviceDown(scene_pos, tp.id());
                   break;
               case Qt::TouchPointMoved:
                   this->current_slide_->OnDeviceMove(scene_pos, tp.id());;
                   break;
               case Qt::TouchPointReleased:
                   this->current_slide_->OnDeviceUp(scene_pos, tp.id());;
                   break;
               default:
                   break;
               }
            }

            return true;
        }
   }
    return QGraphicsView::viewportEvent(event); //must
}


void Widget::UpdateDataSlot(HidMtFingerReport *finger_report)
{
    qDebug() << "geometry:" << this->geometry() << endl;
    qDebug() << "framGeometry:" << this->frameGeometry() << endl;
    event_.EventUpdate(*finger_report, this->frameGeometry());

    if (event_.IsTouchUpdate(*finger_report)) {
        event_.SetFingerReport(*finger_report);
        QList<RawTouchEvent::TouchPoint> *touch_points = event_.touchPoints();//optimization
        foreach (const RawTouchEvent::TouchPoint tp, *touch_points) {
           QPoint touchPos = QPoint(tp.pos().x(), tp.pos().y());
           QPointF scene_pos = this->mapToScene(touchPos.x(), touchPos.y());
           switch(tp.state()) {
           case Qt::TouchPointPressed:
               this->current_slide_->OnDeviceDown(scene_pos, tp.id());
               timer_map_.value(tp.id())->start(100);//200ms
               timer_map_.value(tp.id())->setProperty("id", QVariant(tp.id()));
               this->is_touch_mode_ = true;
               this->current_slide_->SetTouchMode(true);
               break;
           case Qt::TouchPointMoved:
               timer_map_.value(tp.id())->start(100);
               this->current_slide_->OnDeviceMove(scene_pos, tp.id());
               break;
           case Qt::TouchPointReleased:
               if (timer_map_.value(tp.id())->isActive())
                    timer_map_.value(tp.id())->stop();
               this->current_slide_->OnDeviceUp(scene_pos, tp.id());
               this->is_touch_mode_ = false;
               this->current_slide_->SetTouchMode(false);
               break;
           default:
               break;
           }
        }
    }
}

void Widget::HandleTimeOut()
{
    this->is_touch_mode_ = false;
    this->current_slide_->SetTouchMode(false);

    int id = sender()->property("id").toInt();
    this->current_slide_->OnDeviceUp(QPointF(), id);

    timer_map_.value(id)->stop();
}





void Widget::on_pushButton_clicked()
{
    qDebug() << this->current_slide_->GetItemMap().size() << endl;

    if (this->current_slide_->GetItemMap().size() > 0) {
        for (QMap<int, QGraphicsItem*>::iterator it = this->current_slide_->GetItemMap().begin();
             it != this->current_slide_->GetItemMap().end(); it++) {
            this->current_slide_->removeItem(it.value());
           // delete it.value();
        }
        this->current_slide_->GetItemMap().clear();
        //qDebug() <<"count :" << this->current_slide_->count << endl;
    }

        if (this->current_slide_->GetInkMap().size() > 0) {
            for (QMap<int, InkData*>::iterator it = this->current_slide_->GetInkMap().begin();
                 it != this->current_slide_->GetInkMap().end(); ++it) {
                for (int i = 0; i < it.value()->temp_item_.size(); ++i) {
                    this->current_slide_->removeItem(it.value()->temp_item_[i]);
                }
                it.value()->temp_item_.clear();
            }
            this->current_slide_->GetInkMap().clear();
        }
    //this->current_slide_->clear();
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        this->SetInkColor(Qt::green);
        break;
    case 1:
        this->SetInkColor(Qt::red);
        break;
    case 2:
        this->SetInkColor(Qt::black);
        break;
    case 3:
        this->SetInkColor(Qt::yellow);
        break;
    case 4:
        this->SetInkColor(Qt::blue);
        break;
    }
}


void Widget::on_thickness_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    int thickness = ui->thickness->currentIndex()+1;
    this->SetInkThickness(thickness);
}

void Widget::InitTimerMap()
{
    for (int i = 0; i < 10; ++i) {
        timer_map_.insert(i, new QTimer(this));
        connect(timer_map_[i], SIGNAL(timeout()), this, SLOT(HandleTimeOut()));
    }
}

void Widget::DeleteTimerMap()
{
    for (QMap<int, QTimer*>::iterator it = timer_map_.begin();
         it != timer_map_.end(); it++) {
        delete(it.value());
    }
    timer_map_.clear();
}

void Widget::on_GraphicsType_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    switch(ui->GraphicsType->currentIndex()) {
    case 0:
        this->current_slide_->SetGraphicsType("Path");
        break;
    case 1:
        this->current_slide_->SetGraphicsType("Rect");
        break;
    case 2:
        this->current_slide_->SetGraphicsType("Ellipse");
        break;
    case 3:
        this->current_slide_->SetGraphicsType("Line");
        break;
    case 4:
        this->current_slide_->SetGraphicsType("Path");
        this->current_slide_->SetColor(Qt::white);
        this->current_slide_->SetThickness(30);
    default:
        break;
    }
}
