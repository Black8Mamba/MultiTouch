#ifndef SLIDE_H
#define SLIDE_H

#include <QPointF>
#include <QGraphicsScene>
#include <QObject>
#include <QMap>
#include <QVector>
#include "pathelement.h"
#include <QGraphicsSceneMouseEvent>
#include "graphicsfactory.h"


class InkData
{
public:
    InkData()
    {
        this->element_ = Q_NULLPTR;
        this->temp_item_.clear();
    }

public:
    QPointF pre_point_;
    QVector<QGraphicsItem*> temp_item_;
    MyQGraphicsItem *element_;
};

class Slide : public QGraphicsScene
{
    Q_OBJECT
public:
    Slide(QObject *parent = 0);
    ~Slide();

    void SetColor(const QColor& color)          { this->ink_color_ = color; }
    void SetThickness(int thickness)            { this->ink_thickness_ = thickness; }
    void SetTouchMode(bool mode)                { this->is_touch_mode_ = mode; }
    void SetGraphicsType(QString type)          { this->graphics_type_ = type; }
    QMap<int, QGraphicsItem*>& GetItemMap(void) { return this->item_map_; }
    QMap<int, InkData*>& GetInkMap(void)        { return this->ink_map_; }

    void OnDeviceDown(const QPointF& pt, int id = 0);
    void OnDeviceMove(const QPointF& pt, int id = 0);
    void OnDeviceUp(const QPointF& pt, int id = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void DrawStart(InkData *dt);
    void DrawTo(InkData *dt, const QPointF &to);

private:
    QMap<int, InkData*> ink_map_;
    QMap<int, QGraphicsItem*> item_map_;
    int index_;
    QColor ink_color_;
    int ink_thickness_;

    bool is_touch_mode_;

    GraphicsFactory factory_;
    QString graphics_type_;
};

#endif // SLIDE_H
