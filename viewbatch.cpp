#include "viewbatch.h"
#include "ui_viewbatch.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

//所有批次的信息的查看
ViewBatch::ViewBatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewBatch)
{
    ui->setupUi(this);
    QTableWidget* batchInfo = ui->batchInfo;
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
}

ViewBatch::~ViewBatch()
{
    delete ui;
}
