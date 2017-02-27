#include "setproline.h"
#include "ui_setproline.h"

//生产线信息的设置
SetProLine::SetProLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetProLine)
{
    ui->setupUi(this);
}

SetProLine::~SetProLine()
{
    delete ui;
}
