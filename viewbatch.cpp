#include "viewbatch.h"
#include "ui_viewbatch.h"
#include "qres.h"
#include "addbatch.h"
#include "dbhelper.h"
#include "qbatch.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QTreeWidget>
#include <QMessageBox>
#include <QList>
//所有批次的信息的查看
ViewBatch::ViewBatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewBatch)
{
    ui->setupUi(this);
    on_refresh_batch_clicked();
}

ViewBatch::~ViewBatch()
{
    delete ui;
}

void ViewBatch::on_refresh_batch_clicked()
{
    batchList = helper.QgetBatch();
    int l = batchList.length();
    ui->batchInfo->setRowCount(l);
    //设置表格条目
    Qbatch batch;
    for(int i = 0; i<l ;i++)//行
    {
        batch = batchList[i];
        QTableWidgetItem *batchid = new QTableWidgetItem(batch.batchid);
        ui->batchInfo->setItem(i,0,batchid);
        QTableWidgetItem *batchsum = new QTableWidgetItem(batch.batchsum);
        ui->batchInfo->setItem(i,1,batchsum);
        QTableWidgetItem *batchamout = new QTableWidgetItem(batch.batchamout);
        ui->batchInfo->setItem(i,2,batchamout);
    }
}

void ViewBatch::on_add_batch_clicked()
{
    addBatch adb;
    if(adb.exec() == QDialog::Accepted)
    {
        on_data_refresh_clicked();
    }
}

void ViewBatch::on_batchInfo_clicked(const QModelIndex &index)
{
    ui->treeWidget->clear();
    int batchrow=index.row();
    QTreeWidgetItem *batchid = new QTreeWidgetItem(QStringList()<<"A");
    QTreeWidgetItem *trayid = new QTreeWidgetItem(QStringList()<<"B");
    QTreeWidgetItem *productid = new QTreeWidgetItem(QStringList()<<"C");
    ui->treeWidget->addTopLevelItem(batchid);
    ui->treeWidget->addTopLevelItem(trayid);
    ui->treeWidget->addTopLevelItem(productid);
    QStringList columItemList;
    columItemList<<"key"<<"value";
    for(int i=0; i<3; ++i)
    {
        QStringList columItemList;
        QTreeWidgetItem *child;
        QString key;
        key += "a" + QString::number(batchrow);
        columItemList<<key;
        child = new QTreeWidgetItem(columItemList);
        A->addChild(child);
     }
}
