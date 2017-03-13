#include "saveproduct.h"
#include "ui_saveproduct.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDebug>

saveProduct::saveProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveProduct)
{
    ui->setupUi(this);
    // 自适应列宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowCount(1);
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
}

saveProduct::~saveProduct()
{
    delete ui;
}

void saveProduct::setProduct(Product curproduct)
{
    //通过curproduct.id是否为空来判断是要change还是add
    if(curproduct.number != NULL)//非空,change,把原有数据填上
    {
        change = true;
        this->curproduct = curproduct;
        //批次号,托盘号,货物号,货物类型,备注
        QTableWidgetItem *batchid = new QTableWidgetItem(curproduct.batchid);
        ui->tableWidget->setItem(0,0,batchid);
        QTableWidgetItem *tray = new QTableWidgetItem(curproduct.tray);
        ui->tableWidget->setItem(0,1,tray);
        QTableWidgetItem *number = new QTableWidgetItem(curproduct.number);
        ui->tableWidget->setItem(0,2,number);
        QTableWidgetItem *type = new QTableWidgetItem(curproduct.type);
        ui->tableWidget->setItem(0,3,type);
        QTableWidgetItem *flag = new QTableWidgetItem(QObject::tr("%1").arg(curproduct.flag));
        ui->tableWidget->setItem(0,4,flag);
    }else{
        change = false;
    }
}

void saveProduct::on_buttonBox_accepted()
{
    Product pro;
    bool ok;
    pro.flag = ui->tableWidget->item(0,4)->text().toInt(&ok,10);
    //判断是否有未填项
    for(int i = 0; i < 5; i++)
    {
        if(ui->tableWidget->item(0,i)->text() == NULL)
        {
            QMessageBox::warning(this,tr("warning"),tr("All items are required!"));
        }
    }
    pro.batchid = ui->tableWidget->item(0,0)->text();
    pro.tray = ui->tableWidget->item(0,1)->text();
    pro.number = ui->tableWidget->item(0,2)->text();
    pro.type = ui->tableWidget->item(0,3)->text();
    pro.flag = ui->tableWidget->item(0,4)->text().toInt(&ok,10);
    Qres qres;
    if(change)
    {
        qres = helper.QchangeData(userId,curproduct,pro);
    }else {
        qres = helper.QaddDataWhileRefreshBatch(userId, pro);
    }
    if(!qres.success)
    {
        QMessageBox::warning(this,tr("warning"),qres.msg);
        return;
    }
}
