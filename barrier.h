#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class Barrier:public QGraphicsPixmapItem
{
public:
    explicit Barrier(QGraphicsItem *parent=nullptr);
    enum TYPE{
        SPIKE,
        PLANTFORM,
    };
    TYPE get_type() const{return barrier_type;};
    void setInitialX(qreal x) { initial_x = x; };
    qreal initialX() const { return initial_x; };

    QPainterPath shape() const override;

private:
    TYPE barrier_type;
    qreal initial_x;
    QPainterPath barrier_collisionShape;

    void setupAppearance();
    void setupCollision();
};

#endif // BARRIER_H
