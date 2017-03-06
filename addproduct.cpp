#include "addproduct.h"
#include "ui_addproduct.h"
#include <QTableWidgetItem>
#include <QMessageBox>

addProduct::addProduct(QWidget *parent,Product curproduct) :
    QWidget(parent),
    ui(new Ui::addProduct)
{
    ui->setupUi(this);
    // 自适应列宽度,行高,隐藏垂直表头
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setRowCount(1);
    Session curper = Session::getInstance();
    userId = curper.getUserId();
    //通过pro.id是否为空来判断是要change还是add
    if(curproduct.id)//非空,change,把原有数据填上
    {
        change = true;
        QTableWidgetItem *id = new QTableWidgetItem(curproduct.id);
        ui->tableWidget->setItem(0,0,id);
        QTableWidgetItem *number = new QTableWidgetItem(curproduct.number);
        ui->tableWidget->setItem(0,1,number);
        QTableWidgetItem *type = new QTableWidgetItem(curproduct.type);
        ui->tableWidget->setItem(0,2,type);
        QTableWidgetItem *batchid = new QTableWidgetItem(curproduct.batchid);
        ui->tableWidget->setItem(0,3,batchid);
        QTableWidgetItem *tray = new QTableWidgetItem(curproduct.tray);
        ui->tableWidget->setItem(0,4,tray);
        QTableWidgetItem *time = new QTableWidgetItem(curproduct.time);
        ui->tableWidget->setItem(0,5,time);
        QTableWidgetItem *flag = new QTableWidgetItem(curproduct.flag);
        ui->tableWidget->setItem(0,6,flag);
    }else{
        change = false;
    }
}

addProduct::~addProduct()
{
    delete ui;
}

void addProduct::on_save_button_clicked()
{
    Product pro;
    bool ok;
    pro.number = ui->tableWidget->item(0,1)->text();
    pro.type = ui->tableWidget->item(0,2)->text();
    pro.batchid = ui->tableWidget->item(0,3)->text();
    pro.tray = ui->tableWidget->item(0,4)->text();
    pro.time = ui->tableWidget->item(0,5)->text();
    pro.flag = ui->tableWidget->item(0,6)->text().toInt(&ok,10);
    Qres qres;
    if(change)
    {
        qres = helper.QchangeDate(userId,curproduct,pro);
    }else {
        qres = helper.QaddDate(userId, pro);
    }
    if(!qres.success)
    {
        QMessageBox::warning(this,tr("warning"),qres.msg);
    }
    this->close();
}
