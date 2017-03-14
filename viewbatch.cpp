#include "viewbatch.h"
#include "ui_viewbatch.h"
#include "qres.h"
#include "addbatch.h"
#include "dbhelper.h"
#include "qbatch.h"
#include "qtray.h"
#include "product.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QTreeWidget>
#include <QMessageBox>
#include <QList>
#include <QStringList>
#include <QModelIndex>
//所有批次的信息的查看
ViewBatch::ViewBatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewBatch)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
    // 自适应列宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    if( l == 0)
    {
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setSpan(0,0,1,3);
        ui->tableWidget->verticalHeader()->setVisible(false);
        QTableWidgetItem *item = new QTableWidgetItem("还没有任何批次哦~~~");
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(0,0,item);
        ui->tableWidget->setShowGrid(false);//隐藏表格线
        return;
    }
    ui->tableWidget->setRowCount(l);
    //设置表格条目
    Qbatch batch;
    for(int i = 0; i<l ;i++)//行
    {
        batch = batchList[i];
        QTableWidgetItem *batchid = new QTableWidgetItem(batch.batchid);
        batchid->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,0,batchid);
        QTableWidgetItem *batchsum = new QTableWidgetItem(batch.batchsum);
        batchsum->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,1,batchsum);
        QTableWidgetItem *batchamout = new QTableWidgetItem(batch.batchamout);
        batchamout->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,2,batchamout);
    }
}

void ViewBatch::on_add_batch_clicked()
{
    addBatch adb;
    if(adb.exec() == QDialog::Accepted)
    {
        on_refresh_batch_clicked();
    }
}

void ViewBatch::on_tableWidget_clicked(const QModelIndex &index)
{
    ui->treeWidget->clear();
    //树顶:批次号
    QTreeWidgetItem *batchid = new QTreeWidgetItem(ui->treeWidget);
    QString txtbatch = ui->tableWidget->item(index.row(),0)->text();
    batchid->setText(0,txtbatch + " - 批次货物总数:" + ui->tableWidget->item(index.row(),1)->text()
                     + " ; 批次货物已有数: " + ui->tableWidget->item(index.row(),2)->text());//树形控件显示的文本信息
    batchid->setCheckState(0,Qt::Checked); //初始状态没有被选中
    //获取特定批次号所对应的所有托盘号
    QList<Qtray> tlist;
    Qres qre = helper.QgetBatchDetialThroughBatchid(tlist,txtbatch);
    if(!qre.success)
    {
        QMessageBox::warning(this,tr("warning"),qre.msg);
        return;
    }
    //第一层子树:托盘号
    for(int i = 0; i < tlist.length(); i++)
    {
        Qtray tray = tlist[i];
        QTreeWidgetItem* trayTree = new QTreeWidgetItem(batchid);
        trayTree->setText(0,tray.tray + " - 托盘总数:" + QObject::tr("%1").arg(tlist.length()));
        //第二层:货物号
        QList<Product> plist = tray.productlist;
        for(int j = 0; j < plist.length(); j++)
        {
            Product pro = plist[j];
            QTreeWidgetItem* proTree = new QTreeWidgetItem(trayTree);
            proTree->setText(0,pro.number + " - 类型:" + pro.type + " ; 录入时间:" + pro.time
                             + " ; 备注:" + QObject::tr("%1").arg(pro.flag));
        }
    }
}
