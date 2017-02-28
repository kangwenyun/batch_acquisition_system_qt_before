#include "changepasswd.h"
#include "ui_changepasswd.h"
#include "session.h"
#include "utils.h"
#include <QString>
#include <QMessageBox>
#include <QFile>

//密码的设置修改
ChangePasswd::ChangePasswd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswd)
{
    ui->setupUi(this);
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
        //检查原密码是否正确
        //读取本地文件验证密码
        //获取地址
        QString txtName = "../batch_acquisition_system/reg.txt";
        //定义文件对象
        QFile file(txtName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this,tr("打开文件"),tr("打开失败"),file.errorString());
            return;
        }
        bool ok = Utils::verifyPasswd(file,userId,ui->oldKey_edit->text());
        //验证成功即可登录
        if(!ok){
            //提示错误
            ui->err_label->setText(tr("原密码错误！"));
            ui->err_label->show();
            return;
        }
        //检查“新密码”与“确认新密码”是否相等
        if(ui->newKey_edit->text() != ui->newKeyAgain_edit->text())
        {
            //提示错误
            ui->err_label->setText(tr("请确认新密码！"));
            ui->err_label->show();
            return;
        }
        file.close();
        //根据userid去文件查询相关数据删除并写入新信息
        QFile fileIn(txtName);
        if(!fileIn.open(QIODevice::ReadOnly)){
            QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败"),fileIn.errorString());
            return;
        }
        QString fileInfo;
        while(!fileIn.atEnd()){
            QByteArray iLine = fileIn.readLine();
            iLine = iLine.trimmed();
            //需要将读出的一整行数据一同进行转码，而不能在分成list之后对某一项进行转码，会失败
            QString infoLine = QString::fromLocal8Bit(iLine);
            QList<QString> list = infoLine.split(',');
            if(list[0] == userId){
                //找到用户数据
                //替换文件内容当前行
                infoLine.clear();
                infoLine = infoLine + list[0] + ',';
                infoLine = infoLine + list[1] + ',';
                infoLine = infoLine + ui->newKey_edit->text() + ',';
                infoLine = infoLine + list[3] + ',';
                infoLine = infoLine + list[4] + ',';
                infoLine = infoLine + list[5] + '\n';
            }
            fileInfo += infoLine;
        }
        //删除源文件，写入新的同名文件
        fileIn.remove();
        QFile fileOut(txtName);
        if(!fileOut.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败"),fileOut.errorString());
            return;
        }
        QByteArray fileContent = fileInfo.toLocal8Bit();
        fileOut.write(fileContent);
        //没有错误，修改密码成功
        QMessageBox::information(this,tr("修改密码"),tr("修改密码成功！"));
        return;
    }
}
