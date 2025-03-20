#ifndef GAMESENCE_H
#define GAMESENCE_H

#include "character.h"
#include "barrier.h"
#include <QTimer>
#include <QGraphicsScene>

class GameSence : public QGraphicsScene
{
public:
    explicit GameSence(QObject *parent = nullptr);
    void gamestart();
    void Sence_Init();
    // 添加公共访问函数
    Character* getCharacter() const { return character; }

private:
    QTimer timer;
    Character *character;
    QList<Barrier*> barriers;
};

#endif // GAMESENCE_H
