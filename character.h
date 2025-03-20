#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>

class Character :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Character(QGraphicsItem* parent = nullptr);

    void move_left();
    void move_right();
    void jump();

private slots:
    void updateAnimation();

private:
    qreal speedx;
    qreal speedy;
    bool isground();
    QTimer animationTimer;
    int animationFrame;
    QList<QPixmap> animationFrames;
};

#endif // CHARACTER_H
