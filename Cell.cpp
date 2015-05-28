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
    return QRectF(0, 0, 10, 10);
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(item);
    if(_type == '.')
        painter->fillRect(QRectF(1, 1, 9, 9), Qt::blue);
    else if(_type == 'x')
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(20,10,10));
    else if(_type == 'o')
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(150,0,0));
    else
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(100,100,100));
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


