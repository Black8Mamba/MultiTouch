#ifndef PATHELEMENT_H
#define PATHELEMENT_H

#include <QGraphicsPathItem>
#include <QVector>
#include <QPointF>
#include <QGraphicsItem>
#include "kmp.h"
#include <cmath>

class MyQGraphicsItem
{
public:
    MyQGraphicsItem();

    virtual void Render(void) = 0;
    virtual void SetColor( const QColor& color ) = 0;
    virtual void SetThickness( int thickcness ) = 0;
    virtual void SetLayer( qreal zvalue ) = 0;
    virtual QColor Color(void) const = 0;
    virtual int Thickness(void) const = 0;
    virtual QVector<QPointF> Points(void) = 0;
    virtual void AddPoint(const QPointF& pt) = 0;
    QVector<QPointF> list_points_;
protected:

};

class MyPathItem : public MyQGraphicsItem
{
public:
    MyPathItem();
    void Render(void);

    void SetColor( const QColor& color );
    void SetThickness( int thickcness );
    void SetLayer( qreal zvalue );

    QColor Color(void) const { return path_item_.data(KMP_::EPT_Color).value<QColor>(); }
    int Thickness(void) const { return path_item_.data(KMP_::EPT_Thickness).toInt(); }
    QVector<QPointF> Points(void) { return list_points_; }
    void AddPoint(const QPointF& pt) { return list_points_.push_back(pt); }

    QGraphicsPathItem path_item_;

private:
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

    QColor Color(void) const { return path_item_.data(KMP_::EPT_Color).value<QColor>(); }
    int Thickness(void) const { return path_item_.data(KMP_::EPT_Thickness).toInt(); }
    QVector<QPointF> Points(void) { return list_points_; }
    void AddPoint(const QPointF& pt) { return list_points_.push_back(pt); }

    QGraphicsRectItem path_item_;
private:
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

    QColor Color(void) const { return path_item_.data(KMP_::EPT_Color).value<QColor>(); }
    int Thickness(void) const { return path_item_.data(KMP_::EPT_Thickness).toInt(); }
    QVector<QPointF> Points(void) { return list_points_; }
    void AddPoint(const QPointF& pt) { return list_points_.push_back(pt); }

    QGraphicsEllipseItem path_item_;
private:
    void Initialize(void);
};
#endif // PATHELEMENT_H
