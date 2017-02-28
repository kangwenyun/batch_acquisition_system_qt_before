#include "viewdata.h"
#include "ui_viewdata.h"
#include<QFile>
#include<QMessageBox>
//数据的查看
ViewData::ViewData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewData)
{
    ui->setupUi(this);
    // 自适应列宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //select only rows
       ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
       ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

//------------------------------------------------------------------------------------------------------------------------------------------
       //读取文件，确定表格行数
       QString txtName = "../batch_acquisition_system/data.txt";
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
       for(int i = 0; i<l ;i++)//行
       {
           QString str = list[i];
           QList<QString> item = str.split(',');
           for(int j = 0; j<7 ;j++)//列
           {
               QTableWidgetItem *detailInfo = new QTableWidgetItem(item[j]);
              ui->tableWidget->setItem(i,j,detailInfo);
           }
       }
 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
}

ViewData::~ViewData()
{
    delete ui;
}

void ViewData::on_data_change_clicked()
{
     ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);
}

void ViewData::on_data_save_clicked()
{
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
