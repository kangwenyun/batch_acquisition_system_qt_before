#include "changepasswd.h"
#include "ui_changepasswd.h"

//密码的设置修改
ChangePasswd::ChangePasswd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswd)
{
    ui->setupUi(this);
}

ChangePasswd::~ChangePasswd()
{
    delete ui;
}
