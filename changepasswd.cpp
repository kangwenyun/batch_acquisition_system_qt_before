#include "changepasswd.h"
#include "ui_changepasswd.h"
#include "session.h"
#include "utils.h"
#include "qres.h"
#include "dbhelper.h"
#include "qpnglineedit.h"
#include <QString>
#include <QFile>

//密码的设置修改
ChangePasswd::ChangePasswd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswd)
{
    ui->setupUi(this);
    new QPngLineEdit("", ui->userId_edit,"userid.png",1);
    new QPngLineEdit("", ui->oldKey_edit,"oldKey.jpg",1);
    new QPngLineEdit("", ui->newKey_edit,"newKey.jpg",1);
    new QPngLineEdit("", ui->newKeyAgain_edit,"newKey.jpg",1);
    //获取当前数据并将数据信息显示到界面中
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
    ui->userId_edit->setText(userId);
    //账号信息只读,界面上不显示边框
    ui->userId_edit->setReadOnly(true);
    ui->userId_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
    //密码输入以点号显示
    ui->oldKey_edit->setEchoMode(QLineEdit::Password);
    ui->newKey_edit->setEchoMode(QLineEdit::Password);
    ui->newKeyAgain_edit->setEchoMode(QLineEdit::Password);
    //错误提示信息隐藏
    ui->err_label->hide();
    //设置输入框大小
    ui->userId_edit->setFixedHeight(30);
    ui->oldKey_edit->setFixedHeight(30);
    ui->newKey_edit->setFixedHeight(30);
    ui->newKeyAgain_edit->setFixedHeight(30);
    //将焦点设置到原密码输入框上
    ui->oldKey_edit->installEventFilter(this);
    ui->userId_edit->setAlignment(Qt::AlignCenter);
    ui->oldKey_edit->setAlignment(Qt::AlignCenter);
    ui->newKey_edit->setAlignment(Qt::AlignCenter);
    ui->newKeyAgain_edit->setAlignment(Qt::AlignCenter);
}

ChangePasswd::~ChangePasswd()
{
    delete ui;
}

void ChangePasswd::on_ok_button_clicked()
{
    //所有项均为必填项
    if(!ui->oldKey_edit->text().isEmpty()
            && !ui->newKey_edit->text().isEmpty()
            && !ui->newKeyAgain_edit->text().isEmpty())
    {
        //验证"新密码"和"新密码确认"是否一样
        if( ui->newKey_edit->text() == ui->newKeyAgain_edit->text()){
            Qres res =  helper.Qchangepwd(userId,ui->oldKey_edit->text(),ui->newKey_edit->text());
            if(!res.success){
                ui->err_label->setStyleSheet("QLabel{color: rgb(255, 0, 0);}");
            }else{
                ui->err_label->setStyleSheet("QLabel{color: rgb(0, 255, 0);}");
            }
            ui->err_label->setText(res.msg);
            ui->err_label->show();
        }else{
            ui->err_label->setStyleSheet("QLabel{color: rgb(255, 0, 0);}");
            ui->err_label->setText(tr("请确认新密码！"));
            ui->err_label->show();
        }
    }else{
        ui->err_label->setStyleSheet("QLabel{color: rgb(255, 0, 0);}");
        ui->err_label->setText(tr("所有项均为必填项！"));
        ui->err_label->show();
    }
}
