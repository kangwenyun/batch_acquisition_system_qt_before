#include "modifyproline.h"
#include "ui_modifyproline.h"

//生产线信息的修改
ModifyProLine::ModifyProLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyProLine)
{
    ui->setupUi(this);
}

ModifyProLine::~ModifyProLine()
{
    delete ui;
}
