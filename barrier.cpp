#include "barrier.h"
#include "QDebug"

Barrier::Barrier(QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent)
{
    setupAppearance();
    setupCollision();

    // 设置变换原点为中心（方便翻转）
    setTransformOriginPoint(boundingRect().center());

}

// 初始化外观（根据类型加载不同图片）
void Barrier::setupAppearance() {
    switch(barrier_type) {
    case SPIKE:
        setPixmap(QPixmap("E:/我的项目/Qt/running/res/scence/spike.png"));
        break;
    case PLANTFORM:
        setPixmap(QPixmap("E:/我的项目/Qt/running/res/scence/cave_horizontal.png"));
        break;
    default:
        qWarning() << "未知障碍物类型";
        break;
    }
}

void Barrier::setupCollision() {
    switch(barrier_type) {
    case SPIKE: {
        // 尖刺的三角形碰撞区域
        QPolygonF spikeShape;
        spikeShape << QPointF(0, 50)
                   << QPointF(25, 0)
                   << QPointF(50, 50);
        barrier_collisionShape.addPolygon(spikeShape);
        break;
    }
    case PLANTFORM:
        // 平台使用矩形碰撞
        barrier_collisionShape.addRect(0, 0, 100, 20);
        break;
    }
}

QPainterPath Barrier::shape() const {
    return barrier_collisionShape;
}
