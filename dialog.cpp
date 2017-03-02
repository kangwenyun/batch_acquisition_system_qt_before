include "dialog.h"
#include "ui_dialog.h"
#include"dbhelper.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
dbhelper db;
Quser user;
user.userid="aa";
user.passwd="aa";
user.level=0;
db.Qregist(user);
}
