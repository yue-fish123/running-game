#include "gamesence.h"
#include "character.h"
#include "feibiao.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QPainter>

GameSence::GameSence(QObject *parent) : QGraphicsScene(parent), backgroundOffset(0)
{
    viewWidth = 728;
}

void GameSence::gamestart() {
    Sence_Init();

    character = new Character();
    addItem(character);

    character->setPos(0, 300); // 初始位置

    // 定时器更新角色位置（水平方向）
    connect(&timer, &QTimer::timeout, [this]() {
        character->updatePosition();
        //character->setY(character->y() + character->getSpeedY());
    });

    // 启动定时器
    timer.start(20);
    backgroundAndBarriersTimer.start(20);
    barrierGenerationTimer.start(2000); // 每2秒生成一个障碍物

    feibiaoGenerationTimer.setInterval(2000);
    connect(&feibiaoGenerationTimer, &QTimer::timeout, this, &GameSence::generateFeiBiao);
    feibiaoGenerationTimer.start();//生成飞镖

    // 连接定时器信号到槽函数
    connect(&backgroundAndBarriersTimer, &QTimer::timeout, this, &GameSence::updateBackgroundAndBarriers);
    connect(&barrierGenerationTimer, &QTimer::timeout, this, &GameSence::generateRandomBarrier);
    connect(this, &GameSence::gameOver, this, &GameSence::GameOver);
}

void GameSence::Sence_Init() {
    // 加载背景图片（使用资源路径）
    QPixmap bg1(":/res/scence/bg10.png");
    QPixmap bg2(":/res/scence/bg2.png");

    // 创建背景项并添加到场景
    QGraphicsPixmapItem* bgItem1 = new QGraphicsPixmapItem(bg1);
    QGraphicsPixmapItem* bgItem2 = new QGraphicsPixmapItem(bg2);
    bgItem1->setPos(0, 0);
    bgItem2->setPos(bg1.width(), 0); // 第二张图紧接第一张
    addItem(bgItem1);
    addItem(bgItem2);
}

void GameSence::updateBackgroundAndBarriers() {
    if (character->x() >= viewWidth / 2-10) {
        qreal delta = character->getSpeedX_max();
        //获取所有背景项
        QList<QGraphicsPixmapItem*> bgItems;
        for (QGraphicsItem* item : items()) {
            if (auto bg = dynamic_cast<QGraphicsPixmapItem*>(item)) {
                bgItems.append(bg);
            }
        }
        character->set_isInPlantform(false);
        // 移动背景并动态重置
//....................................................................................
        if(getCharacter()->get_isMovingRight()){
            for (QGraphicsPixmapItem* bg : bgItems) {
                bg->setX(bg->x() - delta);
                backgroundOffset+=delta;
                // 当背景完全移出左侧屏幕时
                //这里之所以有这个小于等于14的判断，是因为我的背景资源图宽度比窗口宽了28个像素（左右各14个）。
                //我将背景图部分背景重合，已达到消除两张图片之间的白缝的效果
                if (bg->x() + bg->pixmap().width() <= 14) {
                    // 找到当前所有背景的最大右边界
                    qreal maxRight = 0;
                    for (QGraphicsPixmapItem* otherBg : bgItems) {
                        if (otherBg != bg) {
                            qreal otherRight = otherBg->pixmap().width();
                            maxRight = qMax(maxRight, otherRight);
                        }
                    }
                    // 将当前背景放置到最右侧
                    bg->setX(maxRight-28);
                    //qDebug() << "背景重置到：" << maxRight; // 调试输出
                }
            }
        }
//....................................................................................
      // 移动障碍物
        for (Barrier* barrier : barriers) {
            // 回收超出左侧屏幕的障碍物
            if (barrier->x() + barrier->boundingRect().width() < 0) {
                removeItem(barrier);
                barriers.removeOne(barrier);
                delete barrier;
            }
            else{
                barrier->advance(0);
                barrier->advance(1);
            }
        }
    }
    else{
        return ;
    }

}

void GameSence::generateRandomBarrier() {
    if(backgroundOffset<=1500){
    Barrier::TYPE randomType = static_cast<Barrier::TYPE>(QRandomGenerator::global()->bounded(2)); // 0: SPIKE, 1: SPERA
    Barrier* newBarrier = new Barrier();
    newBarrier->setType(randomType);
    // 根据当前场景偏移生成在右侧屏幕外
    qreal spawnX1 = viewWidth/2 + backgroundOffset/10;
    qreal spawnX2 = viewWidth/3 + backgroundOffset/10;
    if(randomType==0){
        newBarrier->setPos(spawnX1, 360);
    }
    else if(randomType==1){
        newBarrier->setPos(spawnX2,250);
    }

    qreal minDistance = 200; // 最小间距300像素
    if (!barriers.isEmpty()) {
        Barrier* lastBarrier = barriers.last();
        if (lastBarrier->x() > viewWidth - minDistance) {
            return; // 距离太近，跳过本次生成
        }
    }

    addItem(newBarrier);
    barriers.append(newBarrier);

    qDebug() << "生成障碍物，位置X:" << viewWidth + backgroundOffset;

    connect(newBarrier, &Barrier::gameOver, this, &GameSence::gameOver);
    }
}

void GameSence::generateFeiBiao() {
    Attack *newFeiBiao = new Attack();
    connect(newFeiBiao, &Attack::gameOver, this, &GameSence::gameOver);
    addItem(newFeiBiao);
    newFeiBiao->setPos(700, 10); // 设置初始位置
}

void GameSence::GameOver(){
    timer.stop();
    backgroundAndBarriersTimer.stop();
    barrierGenerationTimer.stop();//把所有的计时器给他停了

    QMessageBox msgBox;
    msgBox.setWindowTitle("游戏结束");
    msgBox.setText("你撞到障碍物了！");
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Retry);

    // 处理用户选择
    int ret = msgBox.exec();
    if (ret == QMessageBox::Retry) {
        // 重置游戏
        clear();  // 清理场景
        gamestart();  // 重新开始
    } else {
        qApp->quit();  // 退出程序
    }
}
