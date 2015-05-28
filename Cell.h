#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

class Cell : public QGraphicsItem
{
public:
    Cell(int x, int y, char type);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    void setType(char type);


    char tileType() const;

private:
    int x;
    int y;
    char _type;
};

#endif // CELL_H
