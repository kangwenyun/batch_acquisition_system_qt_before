#include "registered.h"
#include "ui_registered.h"
#include "quser.h"
#include "dbhelper.h"
#include "qres.h"
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
    //添加性别虚拟分组
    genderGroup=new QButtonGroup(this);
    genderGroup->addButton(ui->sex_man,0);
    genderGroup->addButton(ui->sex_women,1);
    //设置默认选中及密码显示形式
    ui->sex_man->setChecked(true);
    ui->passwd->setEchoMode(QLineEdit::Password);
    ui->passwd_again->setEchoMode(QLineEdit::Password);
    ui->err_label->hide();
}

void Registered::on_ok_button_clicked(){
    //获取界面信息
//    QString str;
    //必须项不能为空
    if(!ui->userid->text().isEmpty() && !ui->passwd->text().isEmpty()
            && !ui->passwd_again->text().isEmpty() && !ui->level->text().isEmpty()){
        //“密码”和“确认密码”需保持一致
        if(ui->passwd->text() == ui->passwd_again->text()){
//            str = str + ui->userid->text() + ',';
//            str = str + ui->username->text() + ',';
//            str = str + ui->passwd->text() + ',';
//            str = str + QString("%1").arg(genderGroup->checkedId()) + ',';
//            str = str + ui->age->text() + ',';
//            str = str + ui->job->text() + ',';
//            str = str + ui->level->text();
            Quser user;
            user.userid = ui->userid->text();
            user.username = ui->username->text();
            user.passwd = ui->passwd->text();
            user.age = ui->age->text();
            user.sex = QString("%1").arg(genderGroup->checkedId());
            user.job = ui->job->text();
            user.level = ui->job->text();
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
    //信息提交
    dbhelper helper;
    Qres res = helper.Qregist(user);//返回qres干嘛？

//    //先存放到本地文件
//    //存放地址
//    QString saveName = "../batch_acquisition_system/reg.txt";
//    //定义文件对象
//    QFile fileOut(saveName);
//    if(!fileOut.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
//    {
//        QMessageBox::warning(this,tr("打开文件"),tr("打开失败"),fileOut.errorString());
//        return;
//    }
//    //写数据
//    //构造字节数组写入
//    QByteArray regInfo = str.toLocal8Bit() + '\n';
//    fileOut.write(regInfo);

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
