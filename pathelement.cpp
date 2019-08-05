#include "pathelement.h"
#include <QUuid>
#include <QBrush>
#include <QPen>

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
    for (int i = 1; i < this->list_points_.size(); ++i) {
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
    path_item_.setData(EPT::EPT_Color, v);
}

void MyPathItem::SetThickness(int thickcness)
{
    path_item_.setData(EPT::EPT_Thickness, QVariant(thickcness));
}

void MyPathItem::SetLayer(qreal zvalue)
{
    path_item_.setData(EPT::EPT_Layer, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyPathItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::red);
    path_item_.setData( EPT::EPT_Color,v);
    path_item_.setData( EPT::EPT_Thickness,QVariant(4));
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
    path_item_.setData(EPT::EPT_Color, v);
}

void MyRectItem::SetThickness(int thickcness)
{
    path_item_.setData(EPT::EPT_Thickness, QVariant(thickcness));
}

void MyRectItem::SetLayer(qreal zvalue)
{
    path_item_.setData(EPT::EPT_Layer, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyRectItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::red);
    path_item_.setData( EPT::EPT_Color,v);
    path_item_.setData( EPT::EPT_Thickness,QVariant(4));
}

MyEllipseItem::MyEllipseItem()
{
    ;
}

void MyEllipseItem::Render()
{
    if (this->list_points_.size() < 1)
        return ;
    path_item_.setPen(QPen(QBrush(Color()), (qreal)Thickness(), Qt::SolidLine
                 , Qt::RoundCap, Qt::RoundJoin));

    path_item_.setRect(list_points_[0].x(), list_points_[0].y(),
            abs(list_points_.last().x()-list_points_[0].x()), abs(list_points_.last().y()-list_points_[0].y()));
}

void MyEllipseItem::SetColor(const QColor &color)
{
    QVariant v;
    v.setValue<QColor>(color);
    path_item_.setData(EPT::EPT_Color, v);
}

void MyEllipseItem::SetThickness(int thickcness)
{
    path_item_.setData(EPT::EPT_Thickness, QVariant(thickcness));
}

void MyEllipseItem::SetLayer(qreal zvalue)
{
    path_item_.setData(EPT::EPT_Layer, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyEllipseItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::red);
    path_item_.setData( EPT::EPT_Color,v);
    path_item_.setData( EPT::EPT_Thickness,QVariant(4));
}

MyLineItem::MyLineItem()
{
    ;
}

void MyLineItem::Render()
{
    if (this->list_points_.size() < 1)
        return ;
    path_item_.setPen(QPen(QBrush(Color()), (qreal)Thickness(), Qt::SolidLine
                 , Qt::RoundCap, Qt::RoundJoin));

   // path_item_.setRect(list_points_[0].x(), list_points_[0].y(),
   //         abs(list_points_.last().x()-list_points_[0].x()), abs(list_points_.last().y()-list_points_[0].y()));
    path_item_.setLine(list_points_[0].x(), list_points_[0].y(),
            list_points_.last().x(), list_points_.last().y());
}

void MyLineItem::SetColor(const QColor &color)
{
    QVariant v;
    v.setValue<QColor>(color);
    path_item_.setData(EPT::EPT_Color, v);
}

void MyLineItem::SetThickness(int thickcness)
{
    path_item_.setData(EPT::EPT_Thickness, QVariant(thickcness));
}

void MyLineItem::SetLayer(qreal zvalue)
{
    path_item_.setData(EPT::EPT_Layer, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyLineItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::red);
    path_item_.setData( EPT::EPT_Color,v);
    path_item_.setData( EPT::EPT_Thickness,QVariant(4));
}

