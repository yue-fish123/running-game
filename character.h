#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>

#define WIDTH 728

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Character(QGraphicsItem* parent = nullptr);

    void move_left();
    void move_right();
    void jump();
    void stopMoving();

    qreal getSpeedX() const { return speedx; }
    qreal getSpeedY() const {return speedy;}
    qreal getSpeedX_max() const {return speedx_Max;}

    void set_SpeedX(qreal x) {speedx=x;}
    void set_a(qreal x) {a=x;}

    void set_SpeedY(qreal y) {speedy=y;}
    void set_isJumpling(bool s) {isJumpling=s;}

    void set_isInPlantform(bool a){is_InPlantform=a;}

    bool get_isMovingLeft() const {return isMovingLeft;}
    bool get_isMovingRight() const {return isMovingRight;}

    bool get_isInPlantform() const {return is_InPlantform;}

    void updatePosition();

public slots:
    void updateAnimation();

private:
    qreal speedx;
    qreal speedy;
    qreal speedx_Max;//水平方向的最大速度

    qreal jerkx;//水平方向的急动度
    qreal a;//水平方向的加速度

    bool isground();
    bool is_InPlantform;

    QTimer animationTimer;
    int animationFrame;

    QList<QPixmap> leftAnimationFrames;
    QList<QPixmap> rightAnimationFrames;
    QPixmap idleFrame;

    bool isMovingLeft;
    bool isMovingRight;
    bool isJumpling;

    qreal gravity;
};

#endif // CHARACTER_H
