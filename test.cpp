#include "test.h"
#include "ui_test.h"
<<<<<<< HEAD
#include<dbhelper.h>
#include<session.h>
#include<QDebug>
#include<submitbatch.h>
#include <QApplication>
=======
#include"dbhelper.h"
>>>>>>> 0d5c39fb7e33477d9b670eefe5e3e85335349951
Test::Test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
}

Test::~Test()
{
    delete ui;
}

<<<<<<< HEAD
void Test::on_adddata_clicked()
{

    dbhelper db;
     Session* session=Session::getInstance();
    qDebug()<<session->getUserId();
    Product addproduct;
    addproduct.batchid="A";
    addproduct.flag=1;
    addproduct.number="1";
    addproduct.time="now";
    addproduct.tray="A1";
    addproduct.type="A2";
    db.addDate(session->getUserId(),addproduct);
    //db.addDate();
=======
void Test::on_pushButton_clicked()
{
dbhelper db;
>>>>>>> 0d5c39fb7e33477d9b670eefe5e3e85335349951
}
