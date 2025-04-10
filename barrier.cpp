#include "barrier.h"
#include "QDebug"
#include "qgraphicsscene.h"

Barrier::Barrier(QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsPixmapItem(parent),
    barrier_type(SPIKE),
    initial_x(0),
    currentSpearFrame(0),
    isActivated(false)
{
    setupAppearance();
    setupCollision();

    spear_animationTimer.setInterval(50); // 每50ms更新一帧
    connect(&spear_animationTimer, &QTimer::timeout, this, &Barrier::updateSpearAnimation);
}

// 初始化外观（根据类型加载不同图片）
void Barrier::setupAppearance() {
    switch(barrier_type) {
    case SPIKE:
        setPixmap(QPixmap("E:/我的项目/Qt/running/res/scence/spike.png"));
        break;
    case SPEAR:{
        QString spearPaths[] = {
            "E:/我的项目/Qt/running/res/scence/Spear1.png",
            "E:/我的项目/Qt/running/res/scence/Spear2.png",
            "E:/我的项目/Qt/running/res/scence/Spear3.png",
            "E:/我的项目/Qt/running/res/scence/Spear4.png",
            "E:/我的项目/Qt/running/res/scence/Spear5.png",
            "E:/我的项目/Qt/running/res/scence/Spear6.png",
            "E:/我的项目/Qt/running/res/scence/Spear7.png",
            "E:/我的项目/Qt/running/res/scence/Spear8.png",
            "E:/我的项目/Qt/running/res/scence/Spear9.png",
            "E:/我的项目/Qt/running/res/scence/Spear10.png",
            "E:/我的项目/Qt/running/res/scence/Spear11.png",
            "E:/我的项目/Qt/running/res/scence/Spear12.png",
            "E:/我的项目/Qt/running/res/scence/Spear13.png",
            "E:/我的项目/Qt/running/res/scence/Spear14.png",
            "E:/我的项目/Qt/running/res/scence/Spear15.png",
            "E:/我的项目/Qt/running/res/scence/Spear16.png",
            "E:/我的项目/Qt/running/res/scence/Spear17.png",
        };
        for (const auto& path : spearPaths) {
            SpearFrames.append(QPixmap(path).scaled(QPixmap(path).width() / 5, QPixmap(path).height() / 5));
        }
        setPixmap(SpearFrames.first());
        break;
    }
    default:
        qWarning() << "未知障碍物类型";
        break;
    }
}

void Barrier::setupCollision() {
    switch(barrier_type) {
    case SPIKE: {
        // 尖刺的三角形碰撞区域(尖刺有四个小尖尖)
        QPolygonF spikeShape;
        spikeShape << QPointF(0, 0)
                   << QPointF(10, 18)
                   << QPointF(50, 18)
                   << QPointF(60, 0);
        barrier_collisionShape.addPolygon(spikeShape);
        break;
    }
    case SPEAR:{
        QPolygonF spearShape;
        spearShape<<QPointF(0,0)
                   <<QPointF(5,100)
                   <<QPointF(0,100)
                   <<QPointF(5,0);
        barrier_collisionShape.addPolygon(spearShape);
        break;
    }
    }
}

QPainterPath Barrier::shape() const {
    return barrier_collisionShape;
}

void Barrier::handlecollision(Character *character){
        switch (barrier_type) {
        case SPIKE:
            // 尖刺碰撞：触发游戏结束
            qDebug() << "Game Over!";
            emit gameOver();
            break;
        case SPEAR:
            if(currentSpearFrame >= 5) { // 当动画播放到攻击帧时
                qDebug() << "Game Over! Spear!";
                emit gameOver();
            }
            break;
        }

}

void Barrier::advance(int phase){
    if (phase == 1) { // 仅在第二阶段（逻辑更新阶段）检测碰撞
        // 获取场景中的角色
        QList<QGraphicsItem*> items = scene()->items();
        for (QGraphicsItem* item : items) {
            if (auto character = dynamic_cast<Character*>(item)) {
                if (collidesWithItem(character, Qt::IntersectsItemShape)) {
                    handlecollision(character);
                }
            }
        }
    }

    if (phase == 1 && barrier_type == SPEAR) {
        // 检查场景有效性
        if (!scene()) return;

        // 检测角色接近（水平方向 300 像素内）
        QList<QGraphicsItem*> items = scene()->items();
        for (QGraphicsItem* item : items) {
            if (auto character = dynamic_cast<Character*>(item)) {
                if (qAbs(x() - character->x()) < 300 && !isActivated) {
                    activateSpear();
                }
            }
        }
    }
}

void Barrier::activateSpear()
{
    isActivated = true;
    spear_animationTimer.start();
    QTimer::singleShot(500, [this](){ // 0.5秒后重置
        currentSpearFrame = 0;
        setPixmap(SpearFrames.first());
        isActivated = false;
    });
}

void Barrier::updateSpearAnimation()
{
    // 帧递增逻辑
    if(currentSpearFrame < SpearFrames.size() - 1) {
        currentSpearFrame++;
    } else {
        currentSpearFrame = 0;  // 循环播放时启用
         spear_animationTimer.stop(); // 单次播放时启用
    }

    // 更新显示帧
    if(!SpearFrames.isEmpty()) {
        setPixmap(SpearFrames[currentSpearFrame]);
    }

    // 强制重绘
    update();
}
