#include "character.h"
#include <QDebug>
#include <QKeyEvent>

Character::Character(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(QPixmap(), parent), speedx(0), speedy(-27), speedx_Max(7),jerkx(1),a(2), is_InPlantform(false), animationFrame(0),isMovingLeft(false),isMovingRight(false),isJumpling(false),gravity(1.8)
{
    // 加载静止图片并缩放
    idleFrame = QPixmap("E:/我的项目/Qt/running/res/奶龙图片帧/nailong0.png").scaled(QPixmap("E:/我的项目/Qt/running/res/奶龙图片帧/nailong0.png").width() / 5, QPixmap("E:/我的项目/Qt/running/res/奶龙图片帧/nailong0.png").height() / 5);
    setPixmap(idleFrame);

    // 加载向左动画帧并缩放
    QString leftPaths[] = {
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_left1.png",
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_left2.png",
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_left3.png",
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_left4.png",
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_left5.png"
    };
    for (const auto& path : leftPaths) {
        QPixmap frame = QPixmap(path).scaled(QPixmap(path).width() / 5, QPixmap(path).height() / 5);
        leftAnimationFrames.append(frame);
    }

    // 加载向右动画帧并缩放
    QString rightPaths[] = {
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_right1.png",
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_right2.png",
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_right3.png",
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_right4.png",
        "E:/我的项目/Qt/running/res/奶龙图片帧/nailong_right5.png"
    };
    for (const auto& path : rightPaths) {
        QPixmap frame = QPixmap(path).scaled(QPixmap(path).width() / 5, QPixmap(path).height() / 5);
        rightAnimationFrames.append(frame);
    }

    // 初始化动画定时器
    animationTimer.setInterval(30);
    if (connect(&animationTimer, &QTimer::timeout, this, &Character::updateAnimation)) {
        qDebug() << "Animation timer signal connected successfully";
    } else {
        qDebug() << "Failed to connect animation timer signal";
    }
}

void Character::move_left()
{
    //qDebug() << "Animation timer started for left movement";
    isMovingLeft = true;
    isMovingRight = false;
    if (!animationTimer.isActive()) {
        animationTimer.start(80);
        //qDebug() << "Animation timer started for left movement";
    }
}

void Character::move_right()
{
    isMovingRight = true;
    isMovingLeft = false;
    //qDebug() << "Animation timer started for right movement";
    // 触发背景滚动的条件
    //if (x() >= 728 / 2) {
        // 保持角色在中线，仅移动背景
    //    setX(728 / 2);
    //    speedx=0;
    //}

    if (!animationTimer.isActive()) {
        animationTimer.start(80);
    }
}

void Character::jump()
{
    if (isground()) {
        isJumpling = true;
        speedy = -27;
    }
}

bool Character::isground()
{
    return (y() >= 300);
}

void Character::updateAnimation()
{
    if (isMovingLeft) {
        animationFrame = (animationFrame +1) % leftAnimationFrames.size();
        //qDebug()<<"向左移动切换帧";
        setPixmap(leftAnimationFrames[animationFrame]);
    } else if (isMovingRight) {
        animationFrame = (animationFrame +1) % rightAnimationFrames.size();
        //qDebug()<<"向右移动切换帧";
        setPixmap(rightAnimationFrames[animationFrame]);
    } else {
        setPixmap(idleFrame);
        animationTimer.stop();
    }
}

void Character::updatePosition()
{
    //if (x() + speedx < WIDTH / 2) {
    //    setX(x() + speedx);
    //}

    // 处理竖直方向运动
    if (isJumpling) {
        speedy+=gravity;
        setY(y()+speedy);
        if(isground()){
            speedy=-27;
            isJumpling=false;
        }
    }
    // 处理水平方向运动
    if (isMovingLeft || isMovingRight) {
        speedx += a;
        a += jerkx;
        if (isMovingLeft) {
            if(speedx<=speedx_Max) setX(x()-speedx);
            else setX(x()-speedx_Max);
            if(x()<=0){
                setX(0);
            }
        }
        if (isMovingRight) {
            speedx=qMin(speedx,speedx_Max);
            if (x() < WIDTH / 2) {
                setX(x() + speedx);
            }
            //if(x()>=WIDTH/2){
            //    setX(WIDTH/2);
            //}
        }
    }
    // 触发重绘事件
    update();
}

void Character::stopMoving(){
    isMovingLeft=false;
    isMovingRight=false;
    a=5;
    speedx=0;
}
