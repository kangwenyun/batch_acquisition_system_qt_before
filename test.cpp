#include "test.h"
#include "ui_test.h"
#include"dbhelper.h"
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

void Test::on_pushButton_clicked()
{
dbhelper db;
}
