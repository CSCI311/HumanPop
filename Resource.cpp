#include "Resource.h"

Resource::Resource(int x, int y, int resources) :
    Cell(x,y,'r')
{
    _resources = resources;
}

void Resource::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(item);
    painter->fillRect(QRectF(1, 1, 9, 9), QColor(0,_resources*2,0));
}
int Resource::resources() const
{
    return _resources;
}

void Resource::setResources(int resources)
{
    //Ensure resources does not get out of bounds.
    if(resources < 0)
        _resources = 0;
    else if(resources > 100)
        _resources = 100;
    else
        _resources = resources;
}

