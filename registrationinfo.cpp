#include "registrationinfo.h"
#include "ui_registrationinfo.h"
#include "session.h"
#include "dbhelper.h"
#include "qres.h"
#include "quser.h"
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
    //获取并设置当前用户信息
    Session* curper = Session::getInstance();
    userId = curper->getUserId();
    //根据userid去文件查询相关数据并显示到界面上

//    QString txtName = "../batch_acquisition_system/reg.txt";
//    QFile fileIn(txtName);
//    if(!fileIn.open(QIODevice::ReadOnly)){
//        QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败"),fileIn.errorString());
//        return;
//    }
//    while(!fileIn.atEnd()){
//        QByteArray iLine = fileIn.readLine();
//        iLine = iLine.trimmed();
//        //需要将读出的一整行数据一同进行转码，而不能在分成list之后对某一项进行转码，会失败？
//        QString infoLine = QString::fromLocal8Bit(iLine);
//        QList<QString> list = infoLine.split(',');
//        if(list[0] == userId){
//            //找到用户数据
//            ui->userid_edit->setText(list[0]);
//            ui->username_edit->setText(list[1]);
//            if(list[3] == "0")
//            {
//                ui->sex_edit->setText("男");
//            }else{
//                ui->sex_edit->setText("女");
//            }
//            ui->age_edit->setText(list[4]);
//            ui->job_edit->setText(list[5]);
//            break;
//        }
//    }
//    fileIn.close();
    ui->info_label->hide();
    //将edit都设为只读,不可写
    setWriteability(false);
    ui->userid_edit->setFixedHeight(26);
    ui->username_edit->setFixedHeight(26);
    ui->sex_edit->setFixedHeight(26);
    ui->age_edit->setFixedHeight(26);
    ui->job_edit->setFixedHeight(26);
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
    if(rdOnly)
    {
        //不可写时不显示边框
        //userId永远不可写
        ui->userid_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->username_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->sex_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->age_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
        ui->job_edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
    }else{
        //可写时显示边框
        ui->username_edit->setStyleSheet("QLineEdit{border-width:1}");
        ui->username_edit->setFocus();//聚焦
        ui->username_edit->selectAll();//全选
        ui->sex_edit->setStyleSheet("QLineEdit{border-width:1}");
        ui->age_edit->setStyleSheet("QLineEdit{border-width:1}");
        ui->job_edit->setStyleSheet("QLineEdit{border-width:1}");
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
        dbhelper helper;
        Quser newUser;
        newUser.userid = userId;
        newUser.username = ui->username_edit->text();
        newUser.age = ui->age_edit->text();
        newUser.sex = ui->sex_edit->text();
        newUser.job = ui->job_edit->text();
        newUser.level = ui->level_edit->text();
        Qres res = helper.Qchangeuserinformation( userId, newUser);
        ui->info_label->setText(res.msg);
        ui->info_label->show();

//        QString txtName = "../batch_acquisition_system/reg.txt";
//        QFile fileIn(txtName);
//        if(!fileIn.open(QIODevice::ReadOnly)){
//            QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败"),fileIn.errorString());
//            return;
//        }
//        QString fileInfo;
//        while(!fileIn.atEnd()){
//            QByteArray iLine = fileIn.readLine();
//            iLine = iLine.trimmed();
//            //需要将读出的一整行数据一同进行转码，而不能在分成list之后对某一项进行转码，会失败
//            QString infoLine = QString::fromLocal8Bit(iLine);
//            QList<QString> list = infoLine.split(',');
//            if(list[0] == userId){
//                //找到用户数据
//                //替换文件内容当前行
//                infoLine.clear();
//                infoLine = infoLine + ui->userid_edit->text() + ',';
//                infoLine = infoLine + ui->username_edit->text() + ',';
//                infoLine = infoLine + list[2] + ',';
//                infoLine = infoLine + ui->sex_edit->text() + ',';
//                infoLine = infoLine + ui->age_edit->text() + ',';
//                infoLine = infoLine + ui->job_edit->text() + '\n';
//            }
//            fileInfo += infoLine;
//        }
//        //删除源文件，写入新的同名文件
//        fileIn.remove();
//        QFile fileOut(txtName);
//        if(!fileOut.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
//            QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败"),fileOut.errorString());
//            return;
//        }
//        QByteArray fileContent = fileInfo.toLocal8Bit();
//        fileOut.write(fileContent);
        //改变按钮
        ui->edit_ok_button->setText("编辑");
    }
}
