#include "test.h"
#include "ui_test.h"
#include<login.h>
#include<QPixmap>
#include<QIcon>
#include<viewbatch.h>
test::test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    QPixmap pix(":images/userid.png");
    QIcon icon(pix);
    Login *lo =new Login();
    ViewBatch * vb=new ViewBatch();
    ui->tabWidget->insertTab(0,lo,icon,"register");
    ui->tabWidget->insertTab(1,vb,icon,"vb");

}

test::~test()
{
    delete ui;
}
