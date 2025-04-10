#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamesence.h"
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event1) override;

private:
    Ui::MainWindow *ui;
    QGraphicsView* m_view;  // 游戏视图
    GameSence* m_scene;     // 游戏场景
};
#endif // MAINWINDOW_H
