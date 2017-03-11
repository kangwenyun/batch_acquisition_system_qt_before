#include "registered.h"
#include "ui_registered.h"
#include "quser.h"
#include "dbhelper.h"
#include "qres.h"
#include "qpnglineedit.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QFileDialog>

Registered::Registered(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registered)
{
    ui->setupUi(this);
    new QPngLineEdit("", ui->userid,"userid.png",0);
    new QPngLineEdit("", ui->username,"name.jpg",0);
    new QPngLineEdit("", ui->passwd,"key.png",0);
    new QPngLineEdit("", ui->passwd_again,"key.png",0);
    new QPngLineEdit("", ui->age,"age.jpg",0);
    new QPngLineEdit("", ui->job,"job.jpg",0);
    new QPngLineEdit("", ui->level,"level.jpg",0);
    //添加性别虚拟分组
    genderGroup=new QButtonGroup(this);
    genderGroup->addButton(ui->sex_man,0);
    genderGroup->addButton(ui->sex_women,1);
    //设置默认选中及密码显示形式
    ui->sex_man->setChecked(true);
    ui->passwd->setEchoMode(QLineEdit::Password);
    ui->passwd_again->setEchoMode(QLineEdit::Password);
    ui->err_label->hide();

    ui->userid->setFixedHeight(32);
    ui->username->setFixedHeight(32);
    ui->passwd->setFixedHeight(32);
    ui->passwd_again->setFixedHeight(32);
    ui->age->setFixedHeight(32);
    ui->job->setFixedHeight(32);
    ui->level->setFixedHeight(32);
}

void Registered::on_ok_button_clicked(){
    //获取界面信息
    //必须项不能为空
    Qres res;
    if(!ui->userid->text().isEmpty() && !ui->passwd->text().isEmpty()
            && !ui->passwd_again->text().isEmpty() && !ui->level->text().isEmpty()){
        //“密码”和“确认密码”需保持一致
        if(ui->passwd->text() == ui->passwd_again->text()){
            Quser user;
            user.userid = ui->userid->text();
            user.username = ui->username->text();
            user.passwd = ui->passwd->text();
            user.age = ui->age->text();
            user.sex = QString("%1").arg(genderGroup->checkedId());
            user.job = ui->job->text();
            user.level = ui->level->text();
            //信息提交
            dbhelper helper;
            res = helper.Qregist(user);
        }else{
            //密码不一致
            ui->err_label->setText(tr("请确定密码！"));
            ui->err_label->show();
            return;
        }
    }else{
        //必填项未填
        ui->err_label->setText(tr("请将带*项填满！"));
        ui->err_label->show();
        return;
    }
    if(res.success)
    {
        //注册界面隐藏，登录界面显示
        this->close();
        lg = new Login;
        lg->setUserId(ui->userid->text());
        lg->show();
    }else{
        ui->err_label->setText(res.msg);
    }
}

Registered::~Registered()
{
    delete ui;
}
