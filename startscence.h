#ifndef STARTSCENCE_H
#define STARTSCENCE_H

#include "qpushbutton.h"
#include "QMainWindow"
#include <QDialog>

namespace Ui {
class Startscence;
}

class Startscence : public QDialog
{
    Q_OBJECT

public:
    explicit Startscence(QDialog *parent = nullptr);
    ~Startscence();

private slots:
    void start_game();
    void exit_game();

private:
    Ui::Startscence *ui;

    QPushButton *start;
    QPushButton *exit;
};

#endif // STARTSCENCE_H
