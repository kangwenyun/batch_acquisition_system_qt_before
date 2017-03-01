#include "login.h"
#include "ui_login.h"
#include "registered.h"
#include "getpasswd.h"
#include "mainwindow.h"
#include "session.h"
#include "utils.h"
#include <QCryptographicHash>
#include <QFile>
#include <QList>
#include <QMessageBox>
#include<dbhelper.h>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    //设置密码框的显示模式
    ui->passwd->setEchoMode(QLineEdit::Password);
    ui->err_label->hide();
    ui->userId->setFixedHeight(26);
    ui->passwd->setFixedHeight(26);
}

Login::~Login()
{
    delete ui;
}

void Login::setUserId(QString id){
    userId = id;
    ui->userId->setText(userId);
}

//登录
void Login::on_login_clicked()
{
    //首先判断两编辑框是否有空值
    if(ui->userId->text().isEmpty()
            || ui->passwd->text().isEmpty()){
        ui->err_label->setText(tr("账号/密码不能为空！"));
        ui->err_label->show();
        return;
    }
    //账号
    userId = ui->userId->text();
    //计算密码hash
    passwdHash = QCryptographicHash::hash(ui->passwd->text().toUtf8(),
                                          QCryptographicHash::Sha3_256);
    //请求服务端验证

    //读取本地文件验证密码
    //获取地址
    QString txtName = "../batch_acquisition_system/reg.txt";
    //定义文件对象
    QFile fileIn(txtName);
    if(!fileIn.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,tr("打开文件"),tr("打开失败"),fileIn.errorString());
        return;
    }
    bool success = Utils::verifyPasswd(fileIn,userId,ui->passwd->text());
    //验证成功即可登录
    if(success){
        Session* curper = Session::getInstance();
        curper->setUserId(userId);
        mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
    }else{
        //提示错误
        ui->err_label->setText(tr("用户名或密码错误！"));
        ui->err_label->show();
    }
}

void Login::on_get_passwd_clicked(){
    getPasswd = new GetPasswd;
    getPasswd->show();
    this->close();
}

void Login::on_registered_clicked()
{
    dbhelper db;

    //实例化注册界面
    registered = new Registered;
    //跳转到注册页
    registered->show();

    //关闭登录界面
    this->close();
}
