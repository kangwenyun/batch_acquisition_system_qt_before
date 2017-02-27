#include "viewproline.h"
#include "ui_viewproline.h"

//生产线信息的查看
ViewProLine::ViewProLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewProLine)
{
    ui->setupUi(this);
}

ViewProLine::~ViewProLine()
{
    delete ui;
}
