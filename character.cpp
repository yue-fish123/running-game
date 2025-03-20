#include "character.h"
#include <QDebug>

Character::Character(QGraphicsItem *parent)
    :QObject(), QGraphicsPixmapItem(QPixmap(), parent), speedx(5), speedy(0), animationFrame(0)
{
    // 加载动画帧
    for (int i = 1; i <= 3; ++i) {
        animationFrames.append(QPixmap(QString("E:/我的项目/Qt/running/res/奶龙图片帧/nailong_left%1.png").arg(i)));
    }
    setPixmap(animationFrames[0]);

    // 初始化动画定时器
    animationTimer.setInterval(100);
    connect(&animationTimer, &QTimer::timeout, this, &Character::updateAnimation);
}

void Character::move_left()
{
    setPos(x() - speedx, y());
    if (!animationTimer.isActive()) {
        animationTimer.start();
    }
}

void Character::move_right()
{
    setPos(x() + speedx, y());
    if (!animationTimer.isActive()) {
        animationTimer.start();
    }
}

void Character::jump()
{
    // 简单的跳跃实现
    if (isground()) {
        speedy = -10;
    }
}

bool Character::isground()
{
    // 简单的地面检测，可根据实际情况修改
    return y() >= 300;
}

void Character::updateAnimation()
{
    animationFrame = (animationFrame + 1) % animationFrames.size();
    setPixmap(animationFrames[animationFrame]);
}
