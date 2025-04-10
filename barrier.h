#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include "character.h"

class Barrier: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Barrier(QGraphicsItem *parent = nullptr);
    enum TYPE {
        SPIKE,
        SPEAR
    };
    void setType(TYPE type) { barrier_type = type; setupAppearance(); setupCollision(); }
    TYPE get_type() const { return barrier_type; }
    void setInitialX(qreal x) { initial_x = x; setPos(x, y()); }
    qreal initialX() const { return initial_x; }

    void handlecollision(Character *character);
    QPainterPath shape() const override;

    void activateSpear();

    void advance(int phase) override;

signals:
    void gameOver();

public slots:
    void updateSpearAnimation();

private:
    TYPE barrier_type;
    qreal initial_x;
    QPainterPath barrier_collisionShape;

    QList<QPixmap> SpearFrames;
    QTimer spear_animationTimer;
    int currentSpearFrame;
    bool isActivated;

    void setupAppearance();
    void setupCollision();
};

#endif // BARRIER_H
