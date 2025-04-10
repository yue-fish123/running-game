#ifndef FEIBIAO_H
#define FEIBIAO_H

#include "character.h"
#include "qtimer.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QObject>
#include <QPixmap>

class Attack : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Attack(QObject *parent = nullptr);
    enum ATTACK_TYPE{
        fei_biao,
        Trap_Spike_Run,
    };

    void update_fei_biao_animation();
    void update_fei_biao_position();
    void is_activate_fei_biao();
    void handleCollison(Character *character);

    QPainterPath shape() const override;

signals:
    void gameOver();

public slots:
    void advance(int phase)override;

private slots:
    //void generateFeiBiao();

private:
    QList<QPixmap> fei_biao_Frames;

    QTimer fei_biao_AnimationTimer;//飞镖切帧
    QTimer fei_biao_GenerationTimer;//飞镖定时生成
    QTimer fei_biao_MoveTimer;//飞镖运动定时器

    int current_frames_feibiao;

    qreal fei_biao_speedx;
    qreal fei_biao_speedy;
    qreal fei_biao_gravity;
    qreal fei_biao_a;
    qreal fei_biao_x;
    qreal fei_biao_y;

    QPainterPath feibiao_collisionShape;

    void setupCollision();

};

#endif // FEIBIAO_H
