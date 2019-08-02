#ifndef SLIDE_H
#define SLIDE_H
#include <QPointF>
#include <QGraphicsScene>
#include <QObject>
#include <QMap>
#include <QVector>
#include "pathelement.h"
#include <QGraphicsSceneMouseEvent>


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
    //PathElement *element_;//picture ele
    //RectItem *element_;
    MyQGraphicsItem *element_;
};

class Slide : public QGraphicsScene
{
    Q_OBJECT
public:
    Slide(QObject *parent = 0);
    ~Slide();
    void SetColor(const QColor& color) { this->ink_color_ = color; }
    void SetThickness(int w) { this->ink_thickness_ = w; }
    QMap<int, QGraphicsItem*>& GetItemMap(void) { return this->all_item_; }

    void OnDeviceDown(const QPointF& pt, int id = 0);
    void OnDeviceMove(const QPointF& pt, int id = 0);
    void OnDeviceUp(const QPointF& pt, int id = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void DrawStart(InkData *dt);
    void DrawTo(InkData *dt, const QPointF &to);

//private slots:
//    void UpdateDataSlot(HidMtFingerReport finger_report);

private:
    QMap<int, InkData*> item_map_;
    QMap<int, QGraphicsItem*> all_item_;
    int index_;
    QColor ink_color_;
    int ink_thickness_;
    bool is_drawing_;
};

#endif // SLIDE_H
