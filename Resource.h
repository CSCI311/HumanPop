#ifndef RESOURCE_H
#define RESOURCE_H

#include "Cell.h"
#include <QPainter>


class Resource: public Cell
{
public:
    Resource(int x, int y, int resources);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    int resources() const;
    void setResources(int resources);

private:
    int _resources;
};

#endif // RESOURCE_H
