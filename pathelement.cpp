#include "pathelement.h"
#include <QBrush>
#include <QPen>
#include <QDebug>

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
    path.lineTo(QPointF(this->list_points_.last().x()+0.1, this->list_points_.last().y()+0.1));

    path_item_.setPen(QPen(QBrush(Color()), (qreal)Thickness(), Qt::SolidLine,
                           Qt::RoundCap, Qt::RoundJoin));
    path_item_.setPath(path);
}

void MyPathItem::SetColor(const QColor &color)
{
    QVariant v;
    v.setValue<QColor>(color);
    path_item_.setData(EPT::EPT_COLOR, v);
}

void MyPathItem::SetThickness(int thickcness)
{
    path_item_.setData(EPT::EPT_THICKNESS, QVariant(thickcness));
}

void MyPathItem::SetLayer(qreal zvalue)
{
    path_item_.setData(EPT::EPT_LAYER, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyPathItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::black);
    path_item_.setData( EPT::EPT_COLOR,v);
    path_item_.setData( EPT::EPT_THICKNESS,QVariant(1));
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
    path_item_.setData(EPT::EPT_COLOR, v);
}

void MyRectItem::SetThickness(int thickcness)
{
    path_item_.setData(EPT::EPT_THICKNESS, QVariant(thickcness));
}

void MyRectItem::SetLayer(qreal zvalue)
{
    path_item_.setData(EPT::EPT_LAYER, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyRectItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::black);
    path_item_.setData( EPT::EPT_COLOR,v);
    path_item_.setData( EPT::EPT_THICKNESS,QVariant(1));
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
    path_item_.setData(EPT::EPT_COLOR, v);
}

void MyEllipseItem::SetThickness(int thickcness)
{
    path_item_.setData(EPT::EPT_THICKNESS, QVariant(thickcness));
}

void MyEllipseItem::SetLayer(qreal zvalue)
{
    path_item_.setData(EPT::EPT_LAYER, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyEllipseItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::black);
    path_item_.setData( EPT::EPT_COLOR,v);
    path_item_.setData( EPT::EPT_THICKNESS,QVariant(1));
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

    path_item_.setLine(list_points_[0].x(), list_points_[0].y(),
            list_points_.last().x(), list_points_.last().y());
}

void MyLineItem::SetColor(const QColor &color)
{
    QVariant v;
    v.setValue<QColor>(color);
    path_item_.setData(EPT::EPT_COLOR, v);
}

void MyLineItem::SetThickness(int thickcness)
{
    path_item_.setData(EPT::EPT_THICKNESS, QVariant(thickcness));
}

void MyLineItem::SetLayer(qreal zvalue)
{
    path_item_.setData(EPT::EPT_LAYER, QVariant(zvalue));
    path_item_.setZValue(zvalue);
}

void MyLineItem::Initialize()
{
    QVariant v;
    v.setValue<QColor>(Qt::black);
    path_item_.setData( EPT::EPT_COLOR,v);
    path_item_.setData( EPT::EPT_THICKNESS,QVariant(1));
}

