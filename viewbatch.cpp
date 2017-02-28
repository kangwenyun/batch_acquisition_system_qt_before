#include "viewbatch.h"
#include "ui_viewbatch.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include<QTreeWidget>
#include<QMessageBox>
//所有批次的信息的查看
ViewBatch::ViewBatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewBatch)
{
    ui->setupUi(this);
    batchInfo = ui->batchInfo;
    //读取文件，确定表格行数
    QString txtName = "../batch_acquisition_system/batch.txt";
    QFile fileIn(txtName);
    if(!fileIn.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败"),fileIn.errorString());
        return;
    }
    QList<QString> list;//存放文件中的所有数据
    while(!fileIn.atEnd()){
        QByteArray iLine = fileIn.readLine();
        iLine = iLine.trimmed();
        //需要将读出的一整行数据一同进行转码，而不能在分成list之后对某一项进行转码，会失败？
        QString infoLine = QString::fromLocal8Bit(iLine);
        list.append(infoLine);
    }
    int l = list.length();
    batchInfo->setRowCount(l);
    batchInfo->setColumnCount(3);
    //去除左边的表头
    batchInfo->verticalHeader()->setVisible(false);;
    //将行和列的大小设为与内容相匹配
    batchInfo->resizeColumnsToContents();
    batchInfo->resizeRowsToContents();
    //select only rows
    batchInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不能对表格内容进行修改
    batchInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //自适应列宽度
    batchInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置表格条目
    for(int i = 0; i<l ;i++)//行
    {
        QString str = list[i];
        QList<QString> item = str.split(',');
        for(int j = 0; j<3 ;j++)//列
        {
            QTableWidgetItem *detailInfo = new QTableWidgetItem(item[j]);
            batchInfo->setItem(i,j,detailInfo);
        }
    }
    //升序
    batchInfo->sortItems(0,Qt::AscendingOrder);
    //默认点击第一个

}

ViewBatch::~ViewBatch()
{
    delete ui;
}

void ViewBatch::on_batchInfo_doubleClicked(const QModelIndex &index)
{
   ui->treeWidget->clear();
   int  batchrow=index.row();
<<<<<<< HEAD
   QTreeWidgetItem* A = new QTreeWidgetItem(QStringList()<<"A");
   QTreeWidgetItem* B = new QTreeWidgetItem(QStringList()<<"B");
   QTreeWidgetItem* C = new QTreeWidgetItem(QStringList()<<"C");
   ui->treeWidget->addTopLevelItem(A);
   ui->treeWidget->addTopLevelItem(B);
   ui->treeWidget->addTopLevelItem(C);
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
=======


   QTreeWidget * treewidget =ui->treeWidget;
   for(int i=0;i<3;i++)
   {
       QList<QString>    list;
       list.append("A30"+QString::number(i));
       list.append("A25"+QString::number(i));
       list.append("C50"+QString::number(i));
    QTreeWidgetItem* A = new QTreeWidgetItem(QStringList()<<list.at(i));
     ui->treeWidget->addTopLevelItem(A);
    }

      QStringList columItemList;
      for(int i=0; i<3; ++i)
        {

             QTreeWidgetItem *child;
             QString key;
             key += "a" + QString::number(batchrow);
             columItemList<<key;
             child = new QTreeWidgetItem(columItemList);
            ui->treeWidget->topLevelItem(i)->addChild(child);
         }
>>>>>>> 6623a40dada597d2f8bd877c8203bf8f8bbabef4
}
