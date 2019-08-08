#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include "path_element.h"
#include <QString>


class GraphicsFactory
{
public:
    GraphicsFactory();
    MyQGraphicsItem* CreateGraphicsItem(QString type);
};

#endif // GRAPHICSFACTORY_H
