#ifndef RESOURCE_H
#define RESOURCE_H

#include "Cell.h"
#include <QPainter>


class Resource: public Cell
{
public:
    Resource(int x, int y, int resources);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    float resources() const;
    void setResources(float resources);

private:
    float _resources;
};

#endif // RESOURCE_H
