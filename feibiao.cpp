#include "feibiao.h"
#include "qgraphicsscene.h"
#include "character.h"
#include "gamesence.h"
#include <QDebug>
#include <QRandomGenerator>

Attack::Attack(QObject *parent)
    : QObject{parent},
    current_frames_feibiao(0),
    fei_biao_speedx(1.8),fei_biao_speedy(11),
    fei_biao_gravity(-0.2),fei_biao_a(1.8),
    fei_biao_x(800),fei_biao_y(100)
{
    QString fei_biao_Paths[]={
        "E:/我的项目/Qt/running/res/attack/fei_biao/Suriken1.png",
        "E:/我的项目/Qt/running/res/attack/fei_biao/Suriken2.png",
        "E:/我的项目/Qt/running/res/attack/fei_biao/Suriken3.png",
        "E:/我的项目/Qt/running/res/attack/fei_biao/Suriken4.png",
        "E:/我的项目/Qt/running/res/attack/fei_biao/Suriken5.png",
        "E:/我的项目/Qt/running/res/attack/fei_biao/Suriken6.png",
        "E:/我的项目/Qt/running/res/attack/fei_biao/Suriken7.png",
        "E:/我的项目/Qt/running/res/attack/fei_biao/Suriken8.png",
    };
    for(const auto &path:fei_biao_Paths){
        QPixmap frame=QPixmap(path).scaled(QPixmap(path).width()/6,QPixmap(path).height()/6);
        fei_biao_Frames.append(frame);
    }

    fei_biao_AnimationTimer.setInterval(30);
    connect(&fei_biao_AnimationTimer,&QTimer::timeout,this,&Attack::update_fei_biao_animation);
    fei_biao_AnimationTimer.start();

    //fei_biao_GenerationTimer.setInterval(930);
    //connect(&fei_biao_GenerationTimer, &QTimer::timeout, this, &Attack::generateFeiBiao);
    //fei_biao_GenerationTimer.start();

    fei_biao_MoveTimer.setInterval(25);
    connect(&fei_biao_MoveTimer, &QTimer::timeout, this, &Attack::update_fei_biao_position);
    fei_biao_MoveTimer.start();

    setupCollision();
}

void Attack::update_fei_biao_animation(){
    current_frames_feibiao=(current_frames_feibiao+1)%fei_biao_Frames.size();
    setPixmap(fei_biao_Frames[current_frames_feibiao]);
}

void Attack::update_fei_biao_position(){
    if(fei_biao_x<0||fei_biao_y<0){
        fei_biao_x=800;
        fei_biao_y=10;
        scene()->removeItem(this);
        //qDebug()<<"飞镖滴任务完成了！哈哈哈";
        delete this;
        return;
    }
    else{
        advance(0); // 阶段0
        advance(1); // 阶段1
        fei_biao_speedx+=fei_biao_a;
        fei_biao_speedy+=fei_biao_gravity;
        fei_biao_x-=fei_biao_speedx;
        fei_biao_y+=fei_biao_speedy;
    }
    setX(fei_biao_x);
    setY(fei_biao_y);
    //qDebug() << "飞镖当前位置X:" << fei_biao_x << "Y:" << fei_biao_y;
}
/*
void Attack::generateFeiBiao() {
    // 创建新的飞镖
    Attack *newFeiBiao = new Attack();
    //connect(newFeiBiao, &Attack::gameOver, &GameSence::gameOver);
    // 设置初始位置
    newFeiBiao->setPos(700, 10);
    if (scene()) {
        scene()->addItem(newFeiBiao);
    }
}
*/
void Attack::setupCollision(){
    QPolygonF feibiaoShape;
    feibiaoShape << QPointF(0, 0)
               << QPointF(0, 45)
               << QPointF(45, 45)
               << QPointF(45, 0);
    feibiao_collisionShape.addPolygon(feibiaoShape);
}

void Attack::handleCollison(Character *character){
    qDebug() << "Game Over! Collided with feibiao";
    emit gameOver();
}

QPainterPath Attack::shape() const {
    return feibiao_collisionShape;
}

void Attack::advance(int phase){
    if (phase == 1) {
        QList<QGraphicsItem*> collidingItems = this->collidingItems(Qt::IntersectsItemShape);

        for (QGraphicsItem* item : collidingItems) {
            Character* character = dynamic_cast<Character*>(item);
            if (character) {
                handleCollison(character);
                qDebug() << "Collision detected at:" << pos();
                return; // 只需处理一次碰撞
            }
        }
    }
}
