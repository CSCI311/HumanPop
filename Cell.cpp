#include "Cell.h"

#include <QColor>
#include <QGraphicsItem>
#include <qpainter.h>

Cell::Cell(int x, int y, char type)
{
    this->x = x;
    this->y = y;
    _type = type;
}

QRectF Cell::boundingRect() const
{
    return QRectF(1, 1, 4, 4);
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(1, 1, 4, 4);
    return path;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(item);
    if(_type == '.')
        painter->fillRect(QRectF(0, 0, 5, 5), Qt::blue);
    else if(_type == 'x')
        painter->fillRect(QRectF(0, 0, 5, 5), QColor(80,40,20));
    else if(_type == 'o')
        painter->fillRect(QRectF(0, 0, 5, 5), QColor(150,0,0));
    else
        painter->fillRect(QRectF(0, 0, 5, 5), QColor(100,100,100));
}

void Cell::setType(char type)
{
    if(type == 'o') {
        throw;
    }
    _type = type;
}

char Cell::tileType() const
{
    return _type;
}
int Cell::getX() const
{
    return x;
}

void Cell::setX(int value)
{
    x = value;
}
int Cell::getY() const
{
    return y;
}

void Cell::setY(int value)
{
    y = value;
}




