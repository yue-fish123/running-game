#include "gamesence.h"

GameSence::GameSence(QObject *parent) : QGraphicsScene(parent) {}

void GameSence::gamestart() {
    Sence_Init();

    character = new Character();
    addItem(character);

    // 初始化障碍物
    Barrier* barrier1 = new Barrier();
    barrier1->setInitialX(100);
    barriers.append(barrier1);
    addItem(barrier1);

    // 启动定时器
    timer.start(10);
}

void GameSence::Sence_Init() {
    // 场景初始化代码
}
