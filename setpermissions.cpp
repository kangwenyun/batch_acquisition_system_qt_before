#include "setpermissions.h"
#include "ui_setpermissions.h"

//对不同的用户设置不同的权限
SetPermissions::SetPermissions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetPermissions)
{
    ui->setupUi(this);
}

SetPermissions::~SetPermissions()
{
    delete ui;
}
