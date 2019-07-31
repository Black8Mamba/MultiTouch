#include "pathelement.h"
#include <QUuid>
#include <QBrush>
#include <QPen>

#if 0
void RectItem::Render()
{
    if (this->list_points_.size() < 1)
        return ;
   // QPainterPath path;
   // setRect
    //path.moveTo(this->list_points_[0]);
        //for (size_t i = 1; i < this->list_points_.size(); ++i) {
     //   path.lineTo(this->list_points_[i]);
   // }

    this->setPen(QPen(QBrush(Color()), (qreal)Thickness(), Qt::SolidLine
                 , Qt::RoundCap, Qt::RoundJoin));
    //QRectF rect(QPointF(list_points_[0].x(), list_points_[0].y()),
    //        QPointF(list_points_.last().x(), list_points_.last().y()));
    //this->setRect(rect);
    //this->setPath(path);
    this->setRect(list_points_[0].x(), list_points_[0].y(),
            abs(list_points_.last().x()-list_points_[0].x()), abs(list_points_.last().y()-list_points_[0].y()));
   //this->setPath(path);

}
#endif


MyPathItem::MyPathItem()
{
    ;
}

void MyPathItem::Render()
{
    if (this->list_points_.size() < 1)
        return ;
    QPainterPath path;
    path.moveTo(this->list_points_[0]);
    for (size_t i = 1; i < this->list_points_.size(); ++i) {
        path.lineTo(this->list_points_[i]);
    }

    path_item_.setPen(QPen(QBrush(Color()), (qreal)Thickness(), Qt::SolidLine,
                           Qt::RoundCap, Qt::RoundJoin));
    path_item_.setPath(path);
}

void MyPathItem::SetColor(const QColor &color)
{
    QVariant v;
    v.setValue<QColor>(color);
    path_item_.setData(KMP_::EPT_Color, v);
}

void MyPathItem::SetThickness(int thickcness)
{
    path_item_.setData(KMP_::EPT_Thickness, QVariant(thickcness));
}

void MyPathItem::SetLayer(qreal zvalue)
{
    path_item_.setData(KMP_::EPT_Layer, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyPathItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::red);
    path_item_.setData( KMP_::EPT_Color,v);
    path_item_.setData( KMP_::EPT_Id,QVariant(QUuid::createUuid().toString()));
    path_item_.setData( KMP_::EPT_Thickness,QVariant(4));
    path_item_.setData( KMP_::EPT_Locked,QVariant(false));
    path_item_.setData( KMP_::EPT_Visibiled,QVariant(false ));
}

MyQGraphicsItem::MyQGraphicsItem()
{
    list_points_.clear();
}

MyRectItem::MyRectItem()
{
    ;
}

void MyRectItem::Render()
{
    if (this->list_points_.size() < 1)
        return ;
    path_item_.setPen(QPen(QBrush(Color()), (qreal)Thickness(), Qt::SolidLine
                 , Qt::RoundCap, Qt::RoundJoin));

    path_item_.setRect(list_points_[0].x(), list_points_[0].y(),
            abs(list_points_.last().x()-list_points_[0].x()), abs(list_points_.last().y()-list_points_[0].y()));
}

void MyRectItem::SetColor(const QColor &color)
{
    QVariant v;
    v.setValue<QColor>(color);
    path_item_.setData(KMP_::EPT_Color, v);
}

void MyRectItem::SetThickness(int thickcness)
{
    path_item_.setData(KMP_::EPT_Thickness, QVariant(thickcness));
}

void MyRectItem::SetLayer(qreal zvalue)
{
    path_item_.setData(KMP_::EPT_Layer, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyRectItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::red);
    path_item_.setData( KMP_::EPT_Color,v);
    path_item_.setData( KMP_::EPT_Id,QVariant(QUuid::createUuid().toString()));
    path_item_.setData( KMP_::EPT_Thickness,QVariant(4));
    path_item_.setData( KMP_::EPT_Locked,QVariant(false));
    path_item_.setData( KMP_::EPT_Visibiled,QVariant(false ));
}
