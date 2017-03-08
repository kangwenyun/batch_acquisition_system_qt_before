#include "viewdata.h"
#include "ui_viewdata.h"
#include "session.h"
#include "product.h"
#include <QList>
#include <QTableWidgetItem>

//数据的维护
ViewData::ViewData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewData)
{
    ui->setupUi(this);
    // 自适应列宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //select only rows
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //把选中模式设为单选，即每次只选中一行，而不能选中多行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
    on_data_refresh_clicked();
}

ViewData::~ViewData()
{
    delete ui;
}

void ViewData::on_data_refresh_clicked()
{
    QList<Product> proList = helper.QgetData();
    int l = proList.length();
    ui->tableWidget->setRowCount(l);
    int j = 0;//列计数
    for(int i = 0; i<l ;i++)//行
    {
        j = 0;
        Product pro = proList[i];
        QTableWidgetItem *id = new QTableWidgetItem(QObject::tr("%1").arg(pro.id));
        ui->tableWidget->setItem(i,j++,id);
        QTableWidgetItem *number = new QTableWidgetItem(pro.number);
        ui->tableWidget->setItem(i,j++,number);
        QTableWidgetItem *type = new QTableWidgetItem(pro.type);
        ui->tableWidget->setItem(i,j++,type);
        QTableWidgetItem *batchid = new QTableWidgetItem(pro.batchid);
        ui->tableWidget->setItem(i,j++,batchid);
        QTableWidgetItem *tray = new QTableWidgetItem(pro.tray);
        ui->tableWidget->setItem(i,j++,tray);
        QTableWidgetItem *time = new QTableWidgetItem(pro.time);
        ui->tableWidget->setItem(i,j++,time);
        QTableWidgetItem *flag = new QTableWidgetItem(QObject::tr("%1").arg(pro.flag));
        ui->tableWidget->setItem(i,j++,flag);
    }
}
