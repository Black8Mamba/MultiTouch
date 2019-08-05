#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include "pathelement.h"
#include <QString>


class GraphicsFactory
{
public:
    GraphicsFactory();
    MyQGraphicsItem* CreateGraphicsItem(QString type);
};

#endif // GRAPHICSFACTORY_H
