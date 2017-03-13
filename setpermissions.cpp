#include "setpermissions.h"
#include "ui_setpermissions.h"
#include "session.h"

//对不同的用户设置不同的权限
SetPermissions::SetPermissions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetPermissions)
{
    ui->setupUi(this);
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
}

SetPermissions::~SetPermissions()
{
    delete ui;
}

void SetPermissions::on_change_button_clicked()
{

}
