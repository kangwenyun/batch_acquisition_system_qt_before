#include "registrationinfo.h"
#include "ui_registrationinfo.h"
#include "session.h"
#include "dbhelper.h"
#include "qres.h"
#include "quser.h"
#include "qpnglineedit.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QList>
#include <QByteArray>
#include <QPalette>
#include <QDebug>

//员工注册信息的查看
RegistrationInfo::RegistrationInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationInfo)
{
    ui->setupUi(this);
    new QPngLineEdit("", ui->userid_edit,"userid.png",0);
    new QPngLineEdit("", ui->username_edit,"name.jpg",0);
    new QPngLineEdit("", ui->age_edit,"age.jpg",0);
    new QPngLineEdit("", ui->job_edit,"job.jpg",0);
    new QPngLineEdit("", ui->level_edit,"level.jpg",0);
    //获取并设置当前用户信息
    Session* curper = Session::getInstance();
    userId = curper->getUserId();
//    ui->userid_edit->setAlignment(Qt::AlignCenter);
//    ui->username_edit->setAlignment(Qt::AlignCenter);
//    ui->sex_edit->setAlignment(Qt::AlignCenter);
//    ui->age_edit->setAlignment(Qt::AlignCenter);
//    ui->job_edit->setAlignment(Qt::AlignCenter);
//    ui->level_edit->setAlignment(Qt::AlignCenter);
    //根据userid去查询相关数据并显示到界面上
    Qres qum = helper.QgetUserrmation(newUser,userId);
    if(!qum.success)
    {
        ui->info_label->setText(qum.msg);
        ui->info_label->show();
    }else{
        ui->userid_edit->setText(newUser.userid);
        ui->username_edit->setText(newUser.username);
        if(newUser.sex == "0")
        {
            new QPngLineEdit("", ui->sex_edit,"man.jpg",0);
            ui->sex_edit->setText("♂");
        }else{
            new QPngLineEdit("", ui->sex_edit,"woman.jpg",0);
            ui->sex_edit->setText("♀");
        }
        ui->age_edit->setText(newUser.age);
        ui->job_edit->setText(newUser.job);
        ui->level_edit->setText(newUser.level);
    }
    ui->info_label->hide();
    //将edit都设为只读,不可写
    setWriteability(false);
    ui->userid_edit->setFixedHeight(32);
    ui->username_edit->setFixedHeight(32);
    ui->sex_edit->setFixedHeight(32);
    ui->age_edit->setFixedHeight(32);
    ui->job_edit->setFixedHeight(32);
    ui->level_edit->setFixedHeight(32);
}

RegistrationInfo::~RegistrationInfo()
{
    delete ui;
}

void RegistrationInfo::setWriteability(bool bl)
{
    bool rdOnly = !bl;
    ui->userid_edit->setReadOnly(true);
    ui->username_edit->setReadOnly(rdOnly);
    ui->sex_edit->setReadOnly(rdOnly);
    ui->age_edit->setReadOnly(rdOnly);
    ui->job_edit->setReadOnly(rdOnly);
    ui->level_edit->setReadOnly(rdOnly);
    if(rdOnly)
    {
        //不可写时不显示边框
        //userId永远不可写
        ui->userid_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->username_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->sex_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->age_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->job_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->level_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
    }else{
        //可写时显示边框
        ui->username_edit->setStyleSheet("QLineEdit{border-width:1}");
        ui->username_edit->setFocus();//聚焦
        ui->username_edit->selectAll();//全选
        ui->sex_edit->setStyleSheet("QLineEdit{border-width:1}");
        ui->age_edit->setStyleSheet("QLineEdit{border-width:1}");
        ui->job_edit->setStyleSheet("QLineEdit{border-width:1}");
        ui->level_edit->setStyleSheet("QLineEdit{border-width:1}");
    }
}

void RegistrationInfo::on_edit_ok_button_clicked()
{
    //不可编辑时显示“编辑”，可编辑时显示“确定”
    if("编辑" == ui->edit_ok_button->text())
    {
        //将edit都设为可写
        setWriteability(true);
        //将焦点设置到用户名输入框上
        ui->username_edit->installEventFilter(this);
        //改变按钮
        ui->edit_ok_button->setText("确定");
    }else{
        //将edit都设为只读
        setWriteability(false);
        //根据userid去文件查询相关数据删除并写入新信息
        newUser.userid = userId;
        newUser.username = ui->username_edit->text();
        newUser.age = ui->age_edit->text();
        newUser.sex = ui->sex_edit->text();
        newUser.job = ui->job_edit->text();
        newUser.level = ui->level_edit->text();
        Qres res = helper.Qchangeuserinformation( userId, newUser);
        if(res.success)
        {
            //绿色
            ui->info_label->setStyleSheet("QLabel{color: rgb(0, 255, 0);}");
        }else{
            //红色
            ui->info_label->setStyleSheet("QLabel{color: rgb(255, 0, 0);}");
        }
        ui->info_label->setText(res.msg);
        ui->info_label->show();
        //改变按钮
        ui->edit_ok_button->setText("编辑");
    }
}
