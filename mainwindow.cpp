#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建游戏场景和视图
    m_scene = new GameSence(this);
    m_view = new QGraphicsView(m_scene, this);
    m_view->setFixedSize(728, 448);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //固定视口
    m_view->setSceneRect(0, 0, 728, 448);

    setCentralWidget(m_view);

    // 启动游戏
    m_scene->gamestart();

    m_view->setFocusPolicy(Qt::StrongFocus);
    m_view->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "Key press event received: " << event->key();
    switch (event->key()) {
    case Qt::Key_A:
        m_scene->getCharacter()->move_left();
        //qDebug() << "Left key pressed";
        break;
    case Qt::Key_D:
        m_scene->getCharacter()->move_right();
        //qDebug() << "Right key pressed";
        break;
    case Qt::Key_Space:
        m_scene->getCharacter()->jump();
        //qDebug() << "Space key pressed";
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event1)
{
    switch (event1->key()) {
    case Qt::Key_A:
        m_scene->getCharacter()->stopMoving();
        break;
    case Qt::Key_D:
        m_scene->getCharacter()->stopMoving();
        break;
    default:
        QMainWindow::keyReleaseEvent(event1);
    }
}
