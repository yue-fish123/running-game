#ifndef GAMESENCE_H
#define GAMESENCE_H

#include "character.h"
#include "barrier.h"
#include "character.h"
#include <QTimer>
#include <QMessageBox>
#include <QApplication>
#include <QGraphicsScene>
#include <QPixmap>

class GameSence : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameSence(QObject *parent = nullptr);
    void gamestart();
    void Sence_Init();
    Character* getCharacter() const { return character; }

signals:
    void gameOver();

private slots:
    void updateBackgroundAndBarriers();
    void generateRandomBarrier();
    void GameOver();
    void generateFeiBiao();

private:
    QTimer timer;
    QTimer backgroundAndBarriersTimer;
    QTimer barrierGenerationTimer;
    QTimer feibiaoGenerationTimer;

    Character *character;
    QList<Barrier*> barriers;
    QPixmap backgroundImage1;
    QPixmap backgroundImage2;
    int backgroundOffset;
    int viewWidth;

    QPainter painter;
};

#endif // GAMESENCE_H
