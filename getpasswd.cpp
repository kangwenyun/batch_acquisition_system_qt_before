#include "getpasswd.h"
#include "login.h"
#include "ui_getpasswd.h"

GetPasswd::GetPasswd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetPasswd)
{
    ui->setupUi(this);
    ui->verification_edit->setPlaceholderText(tr("请输入"));
    ui->error_label->hide();
}

GetPasswd::~GetPasswd()
{
    delete ui;
}

void GetPasswd::on_pushButton_clicked()
{
    //验证成功返回登录界面，失败提示
    if(ui->verification_edit->text() == "123"){
        lg = new Login();
        lg->show();
        this->close();
    }else{
        ui->error_label->show();
        return;
    }
}
