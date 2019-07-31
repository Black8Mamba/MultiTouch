#include "slide.h"
#include <QDebug>
#include <string>
using std::string;

Slide::Slide(QObject *parent)
    :QGraphicsScene(parent)
{
    this->is_drawing_ = false;
    qRegisterMetaType<HidMtFingerReport>("HidMtFingerReport");
    connect(&thread_, SIGNAL(UpdateDataSignal(HidMtFingerReport)),
               this, SLOT(UpdateDataSlot(HidMtFingerReport)));
    thread_.start();
}

Slide::~Slide()
{
    thread_.stop();
}

void Slide::OnDeviceDown(const QPointF &pt, int id)
{
    if (item_map_.keys().contains(id)) {

        InkData *dt = item_map_.value(id);
        MyPathItem *my_item = static_cast<MyPathItem *>(dt->element_);
        if (dt->element_) {
            //QGraphicsScene::removeItem(dt->element_);
            QGraphicsScene::removeItem(static_cast<QGraphicsItem*>(&my_item->path_item_));
        }
        if (dt->temp_item_.size() > 1) {
            for (int i = 0; i < dt->temp_item_.size(); ++i)
                QGraphicsScene::removeItem(dt->temp_item_[i]);
        }
        dt->temp_item_.clear();
        delete dt;
        item_map_.remove(id);
    }

    InkData *dt = new InkData;
    dt->pre_point_ = pt;
    //dt->element_ = new PathElement;
    //dt->element_ = new RectItem;
   //dt->element_ = new MyPathItem;
    //dt->element_ = new MyEllipseItem;
   // dt->element_ = dynamic_cast<MyQGraphicsItem*>(new MyRectItem);
    dt->element_ = new MyLineItem;
    dt->element_->AddPoint(pt);
    item_map_.insert(id, dt);
    this->DrawStart(dt);
}

void Slide::OnDeviceMove(const QPointF &pt, int id)
{
    if (item_map_.keys().contains(id)) {
        InkData *dt = item_map_.value(id);
        QPointF to = pt;
        if (dt->element_)
            dt->element_->AddPoint(to);

        this->DrawTo(dt, to);
        dt->pre_point_ = to;
    }
}

void Slide::OnDeviceUp(const QPointF &pt, int id)
{
    Q_UNUSED(pt);

    if (item_map_.keys().contains(id)) {
        InkData *dt = item_map_.value(id);
        for (int i = 0; i < dt->temp_item_.size(); ++i) {
            QGraphicsScene::removeItem(dt->temp_item_[i]);
        }

        dt->temp_item_.clear();
        dt->element_->SetColor(ink_color_);
        dt->element_->SetThickness(ink_thickness_);
        dt->element_->Render();//
        //QGraphicsScene::addItem(dt->element_);
        MyPathItem* my_path = static_cast<MyPathItem*>(dt->element_);
        QGraphicsScene::addItem(static_cast<QGraphicsItem*>(&my_path->path_item_));

        item_map_.remove(id);
    }
}

void Slide::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->is_drawing_ = true;
    this->OnDeviceDown(event->scenePos());
}

void Slide::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->is_drawing_) {
        this->OnDeviceMove(event->scenePos());
    }
}

void Slide::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->is_drawing_) {
        this->is_drawing_ = false;
        this->OnDeviceUp(event->scenePos());
    }
}

void Slide::DrawStart(InkData *dt)
{
    qreal x = dt->pre_point_.x() - ink_thickness_/2.f;
    qreal y = dt->pre_point_.y() - ink_thickness_/2.f;

    QGraphicsEllipseItem *el = addEllipse(QRect(x, y, ink_thickness_, ink_thickness_),
                                          QPen(ink_color_, 1), QBrush(ink_color_));
    dt->temp_item_.push_back(el);
}

void Slide::DrawTo(InkData *dt, const QPointF &to)//use RTTI to identify
{
    MyQGraphicsItem &class_type = *(dt->element_);
    qDebug() << typeid(class_type).name()<< endl;
    if (typeid(class_type).name() == string("10MyRectItem")) {
         QGraphicsScene::removeItem(dt->temp_item_.back());
         dt->temp_item_.pop_back();
      QGraphicsRectItem* li = addRect(dt->element_->list_points_[0].x(),
              dt->element_->list_points_[0].y(),
              dt->pre_point_.x() - dt->element_->list_points_[0].x(),
              dt->pre_point_.y() - dt->element_->list_points_[0].y(),
              QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                 Qt::RoundCap, Qt::RoundJoin));
      dt->temp_item_.push_back(li);
    } else if (typeid(class_type).name() == string("10MyPathItem")) {
    QGraphicsLineItem* li = addLine(dt->pre_point_.x(),
                                    dt->pre_point_.y(),
                                    to.x(), to.y(),
                                    QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                                         Qt::RoundCap, Qt::RoundJoin));
    dt->temp_item_.push_back(li);
    } else if (typeid(class_type).name() == string("13MyEllipseItem")) {
        QGraphicsScene::removeItem(dt->temp_item_.back());
        dt->temp_item_.pop_back();
        QGraphicsEllipseItem* li = addEllipse(dt->element_->list_points_[0].x(),
                dt->element_->list_points_[0].y(),
                dt->pre_point_.x() - dt->element_->list_points_[0].x(),
                dt->pre_point_.y() - dt->element_->list_points_[0].y(),
                QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                     Qt::RoundCap, Qt::RoundJoin));
        dt->temp_item_.push_back(li);
    } else if (typeid(class_type).name() == string("10MyLineItem")) {
        QGraphicsScene::removeItem(dt->temp_item_.back());
        dt->temp_item_.pop_back();
        QGraphicsLineItem* li = addLine(dt->element_->list_points_[0].x(),
                dt->element_->list_points_[0].y(),
                dt->pre_point_.x(),
                dt->pre_point_.y(),
                QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                     Qt::RoundCap, Qt::RoundJoin));
        dt->temp_item_.push_back(li);
    }

    //qDebug() << "typeid: " << typeid(p).name() << endl;
}

void Slide::UpdateDataSlot(HidMtFingerReport finger_report)
{
    qDebug() << "update" << endl;
    qDebug() << finger_report.count << endl;
    event_.EventUpdate(finger_report);
    if (event_.GetDown()) {
        qDebug() << "down" << endl;
        //start_point_ = event_.GetPos();
       // qDebug() << "startPoint x " << start_point_.x() << endl;
       // qDebug() << "startPoint y " << start_point_.y() << endl;
        //touch_status = down_;
        //update();
    } else if (event_.GetMove()) {
        qDebug() << "move" << endl;
        //end_point_ = event_.GetPos();
       // qDebug() << "endPoint x " << end_point_.x() << endl;
       // qDebug() << "endPoint y " << end_point_.y() << endl;
       // tempPix_ = pix_;
       // touch_status = move_;
        //update();
    } else if (event_.GetUp()) {
        qDebug() << "up" << endl;
       // end_point_ = event_.GetPos();
       // qDebug() << "endPoint x " << end_point_.x() << endl;
      //  qDebug() << "endPoint y " << end_point_.y() << endl;
      // touch_status = up_;
        //update();
    }
    fflush(stdout);
}





