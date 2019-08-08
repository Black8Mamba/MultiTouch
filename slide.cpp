#include "slide.h"
#include <QDebug>
#include <string>

using std::string;

Slide::Slide(QObject *parent)
    :QGraphicsScene(parent)
{
    this->index_ = 0;
    this->graphics_type_ = "Path";
}

Slide::~Slide()
{
    ;
}

void Slide::OnDeviceDown(const QPointF &pt, int id)
{

    if (ink_map_.keys().contains(id)) {

        InkData *dt = ink_map_.value(id);
        if (dt->element_) {
            QGraphicsScene::removeItem(dt->element_->returnItem());
        }

        if (dt->temp_item_.size() > 1) {
            for (int i = 0; i < dt->temp_item_.size(); ++i)
                QGraphicsScene::removeItem(dt->temp_item_[i]);
        }

        dt->temp_item_.clear();
        delete dt;
        ink_map_.remove(id);
    }


    InkData *dt = new InkData;
    dt->pre_point_ = pt;
    dt->element_ = factory_.CreateGraphicsItem(graphics_type_);
    dt->element_->AddPoint(pt);
    ink_map_.insert(id, dt);
    this->DrawStart(dt);
}

void Slide::OnDeviceMove(const QPointF &pt, int id)
{
    if (ink_map_.keys().contains(id)) {
        InkData *dt = ink_map_.value(id);
        QPointF to = pt;
        if (dt->element_) {
            dt->element_->AddPoint(to);
            this->DrawTo(dt, to);
            dt->pre_point_ = to;
        }
    }
}

void Slide::OnDeviceUp(const QPointF &pt, int id)
{
    Q_UNUSED(pt);

    if (ink_map_.keys().contains(id)) {
        InkData *dt = ink_map_.value(id);

        for (int i = 0; i < dt->temp_item_.size(); ++i) {
            QGraphicsScene::removeItem(dt->temp_item_[i]);
        }

        dt->temp_item_.clear();
        dt->element_->SetColor(ink_color_);
        dt->element_->SetThickness(ink_thickness_);
        dt->element_->Render();

        QGraphicsScene::addItem(dt->element_->returnItem());
        item_map_.insert(index_++, dt->element_->returnItem());
        ink_map_.remove(id);
    }
}

void Slide::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!is_touch_mode_) {
        this->OnDeviceDown(event->scenePos());
    }

}

void Slide::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!is_touch_mode_) {
        this->OnDeviceMove(event->scenePos());
    }
}

void Slide::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!is_touch_mode_){
        this->OnDeviceUp(event->scenePos());

    }
}

void Slide::DrawStart(InkData *dt)
{
    if (dt == Q_NULLPTR)
        return ;

    qreal x = dt->pre_point_.x();// - ink_thickness_/2.f;
    qreal y = dt->pre_point_.y();// - ink_thickness_/2.f;

    QGraphicsEllipseItem *el = addEllipse(QRect(x, y, ink_thickness_, ink_thickness_),
                                          QPen(ink_color_, 1), QBrush(ink_color_));
    dt->temp_item_.push_back(el);
}

void Slide::DrawTo(InkData *dt, const QPointF &to)//use RTTI to identify graphics
{
    if (dt == Q_NULLPTR)
        return ;

    MyQGraphicsItem &class_type = *(dt->element_);
   // qDebug() << typeid(class_type).name()<< endl;

    if (typeid(class_type).name() == string("10MyRectItem")) {
         QGraphicsScene::removeItem(dt->temp_item_.back());
         dt->temp_item_.pop_back();

      QGraphicsRectItem* li = addRect(dt->element_->GetPointsList()[0].x(),
              dt->element_->GetPointsList()[0].y(),
              dt->pre_point_.x() - dt->element_->GetPointsList()[0].x(),
              dt->pre_point_.y() - dt->element_->GetPointsList()[0].y(),
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

        QGraphicsEllipseItem* li = addEllipse(dt->element_->GetPointsList()[0].x(),
                dt->element_->GetPointsList()[0].y(),
                dt->pre_point_.x() - dt->element_->GetPointsList()[0].x(),
                dt->pre_point_.y() - dt->element_->GetPointsList()[0].y(),
                QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                     Qt::RoundCap, Qt::RoundJoin));

        dt->temp_item_.push_back(li);
    } else if (typeid(class_type).name() == string("10MyLineItem")) {
        QGraphicsScene::removeItem(dt->temp_item_.back());
        dt->temp_item_.pop_back();

        QGraphicsLineItem* li = addLine(dt->element_->GetPointsList()[0].x(),
                dt->element_->GetPointsList()[0].y(),
                dt->pre_point_.x(),
                dt->pre_point_.y(),
                QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                     Qt::RoundCap, Qt::RoundJoin));

        dt->temp_item_.push_back(li);
    }
}

#if 0
void Slide::DrawTo(InkData *dt, const QPointF &to)//use RTTI to identify graphics
{
    if (dt == Q_NULLPTR)
        return ;

    MyQGraphicsItem &class_type = *(dt->element_);
   // qDebug() << typeid(class_type).name()<< endl;

    //if (typeid(class_type).name() == "10MyRectItem") {
    if (strstr(typeid(class_type).name(), "MyRectItem")) {
         QGraphicsScene::removeItem(dt->temp_item_.back());
         dt->temp_item_.pop_back();

      QGraphicsRectItem* li = addRect(dt->element_->GetPointsList()[0].x(),
              dt->element_->GetPointsList()[0].y(),
              dt->pre_point_.x() - dt->element_->GetPointsList()[0].x(),
              dt->pre_point_.y() - dt->element_->GetPointsList()[0].y(),
              QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                 Qt::RoundCap, Qt::RoundJoin));

      dt->temp_item_.push_back(li);
    } else if (strstr(typeid(class_type).name(), "MyPathItem")) {
    QGraphicsLineItem* li = addLine(dt->pre_point_.x(),
                                    dt->pre_point_.y(),
                                    to.x(), to.y(),
                                    QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                                         Qt::RoundCap, Qt::RoundJoin));
    dt->temp_item_.push_back(li);
    } else if (strstr(typeid(class_type).name(), "MyEllipseItem")) {
        QGraphicsScene::removeItem(dt->temp_item_.back());
        dt->temp_item_.pop_back();

        QGraphicsEllipseItem* li = addEllipse(dt->element_->GetPointsList()[0].x(),
                dt->element_->GetPointsList()[0].y(),
                dt->pre_point_.x() - dt->element_->GetPointsList()[0].x(),
                dt->pre_point_.y() - dt->element_->GetPointsList()[0].y(),
                QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                     Qt::RoundCap, Qt::RoundJoin));

        dt->temp_item_.push_back(li);
    } else if (strstr(typeid(class_type).name(), "MyLineItem")) {
        QGraphicsScene::removeItem(dt->temp_item_.back());
        dt->temp_item_.pop_back();

        QGraphicsLineItem* li = addLine(dt->element_->GetPointsList()[0].x(),
                dt->element_->GetPointsList()[0].y(),
                dt->pre_point_.x(),
                dt->pre_point_.y(),
                QPen(QBrush(ink_color_), ink_thickness_, Qt::SolidLine,
                     Qt::RoundCap, Qt::RoundJoin));

        dt->temp_item_.push_back(li);
    }
}
#endif






