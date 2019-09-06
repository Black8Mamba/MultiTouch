/*
 * @Description: In User Settings Edit
 * @Author: Yongjie
 * @Date: 2019-09-06 14:42:29
 * @LastEditTime: 2019-09-06 19:12:30
 * @LastEditors: Please set LastEditors
 */
#ifndef PATHELEMENT_H
#define PATHELEMENT_H

#include <QGraphicsPathItem>
#include <QVector>
#include <QPointF>
#include <QGraphicsItem>
#include "ept.h"
#include <cmath>

class MyQGraphicsItem
{
public:
    MyQGraphicsItem();

    virtual void Render(void) = 0; //绘制函数
    virtual void SetColor( const QColor& color ) = 0;
    virtual void SetThickness( int thickcness ) = 0;
    virtual void SetLayer( qreal zvalue ) = 0;

    virtual QColor Color(void) const = 0;
    virtual int Thickness(void) const = 0;
    virtual QGraphicsItem* returnItem(void) = 0;

    QVector<QPointF> GetPointsList() { return list_points_; }
    void AddPoint(const QPointF& pt) { list_points_.push_back(pt); }

protected:
        QVector<QPointF> list_points_;
};

class MyPathItem : public MyQGraphicsItem
{
public:
    MyPathItem();
    void Render(void);

    void SetColor( const QColor& color );
    void SetThickness( int thickcness );
    void SetLayer( qreal zvalue );


    QColor Color(void) const { return path_item_.data(EPT::EPT_COLOR).value<QColor>(); }
    int Thickness(void) const { return path_item_.data(EPT::EPT_THICKNESS).toInt(); }
    virtual QGraphicsItem* returnItem(void) { return &path_item_; }

private:
    QGraphicsPathItem path_item_;
    void Initialize(void);
};

class MyRectItem : public MyQGraphicsItem
{
public:
    MyRectItem();

    void Render(void);
    void SetColor( const QColor& color );
    void SetThickness( int thickcness );
    void SetLayer( qreal zvalue );

    QColor Color(void) const { return path_item_.data(EPT::EPT_COLOR).value<QColor>(); }
    int Thickness(void) const { return path_item_.data(EPT::EPT_THICKNESS).toInt(); }
    virtual QGraphicsItem* returnItem(void) { return &path_item_; }


private:
    QGraphicsRectItem path_item_;
    void Initialize(void);
};

class MyEllipseItem : public MyQGraphicsItem
{
public:
    MyEllipseItem();
    void Render(void);
    void SetColor( const QColor& color );
    void SetThickness( int thickcness );
    void SetLayer( qreal zvalue );

    QColor Color(void) const { return path_item_.data(EPT::EPT_COLOR).value<QColor>(); }
    int Thickness(void) const { return path_item_.data(EPT::EPT_THICKNESS).toInt(); }
    virtual QGraphicsItem* returnItem(void) { return &path_item_; }

private:
    void Initialize(void);
    QGraphicsEllipseItem path_item_;
};

class MyLineItem : public MyQGraphicsItem
{
public:
    MyLineItem();
    void Render(void);
    void SetColor( const QColor& color );
    void SetThickness( int thickcness );
    void SetLayer( qreal zvalue );

    QColor Color(void) const { return path_item_.data(EPT::EPT_COLOR).value<QColor>(); }
    int Thickness(void) const { return path_item_.data(EPT::EPT_THICKNESS).toInt(); }
    virtual QGraphicsItem* returnItem(void) { return &path_item_; }

private:
    QGraphicsLineItem path_item_;
    void Initialize(void);
};

#endif // PATHELEMENT_H
