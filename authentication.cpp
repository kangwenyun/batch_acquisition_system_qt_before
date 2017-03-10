#include "authentication.h"
#include "ui_authentication.h"
//系统登录，身份认证
Authentication::Authentication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Authentication)
{
    ui->setupUi(this);
}

Authentication::~Authentication()
{
    delete ui;
}

void Authentication::on_pushButton_clicked()
{
//Test * test=new Test();
//test->show();
}
