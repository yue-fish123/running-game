#include "startscence.h"
#include "QApplication"
#include "ui_startscence.h"

Startscence::Startscence(QDialog *parent)
    : QDialog(parent),ui(new Ui::Startscence)
{
    ui->setupUi(this);

    setFixedSize(728,448);

    start=ui->pushButton;
    exit=ui->pushButton_2;

    ui->pushButton->setFixedSize(150, 75);
    ui->pushButton_2->setFixedSize(150,75);//设置按钮的大小

    start->move(270,220);
    exit->move(270,320);

    connect(start,&QPushButton::clicked,this,&Startscence::start_game);
    connect(exit,&QPushButton::clicked,this,&Startscence::exit_game);
}

Startscence::~Startscence(){
    delete ui;
}

void Startscence::start_game(){
    accept();
}

void Startscence::exit_game(){
    reject();
}
