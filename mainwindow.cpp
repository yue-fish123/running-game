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
    m_view->setFixedSize(800, 600);
    setCentralWidget(m_view);

    // 启动游戏
    m_scene->gamestart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        // 使用公共访问函数获取 character 指针
        m_scene->getCharacter()->move_left();
        break;
    case Qt::Key_Right:
        m_scene->getCharacter()->move_right();
        break;
    case Qt::Key_Space:
        m_scene->getCharacter()->jump();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}
