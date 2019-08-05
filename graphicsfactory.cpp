#include "graphicsfactory.h"

GraphicsFactory::GraphicsFactory()
{
    ;
}

MyQGraphicsItem *GraphicsFactory::CreateGraphicsItem(QString type)
{
    if (type == "Path")
        return new MyPathItem;
    else if (type == "Rect")
        return new MyRectItem;
    else if (type == "Ellipse")
        return new MyEllipseItem;
    else if (type == "Line")
        return new MyLineItem;
    else
        return NULL;
}

