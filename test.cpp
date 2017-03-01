#include "test.h"
#include "ui_test.h"
#include<dbhelper.h>
#include<session.h>
#include<QDebug>
#include<submitbatch.h>
#include <QApplication>
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
}
