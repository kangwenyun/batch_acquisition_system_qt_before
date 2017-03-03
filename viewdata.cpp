#include "viewdata.h"
#include "ui_viewdata.h"
#include "dbhelper.h"
#include "product.h"
#include <QList>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
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
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    on_data_refresh_clicked();

//------------------------------------------------------------------------------------------------------------------------------------------
//       //读取文件，确定表格行数
//       QString txtName = "../batch_acquisition_system/data.txt";
//       QFile fileIn(txtName);
//       if(!fileIn.open(QIODevice::ReadOnly)){
//           QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败"),fileIn.errorString());
//           return;
//       }
//       QList<QString> list;//存放文件中的所有数据
//       while(!fileIn.atEnd()){
//           QByteArray iLine = fileIn.readLine();
//           iLine = iLine.trimmed();
//           //需要将读出的一整行数据一同进行转码，而不能在分成list之后对某一项进行转码，会失败？
//           QString infoLine = QString::fromLocal8Bit(iLine);
//           list.append(infoLine);
//       }
//       int l = list.length();
//       for(int i = 0; i<l ;i++)//行
//       {
//           QString str = list[i];
//           QList<QString> item = str.split(',');
//           for(int j = 0; j<7 ;j++)//列
//           {
//               QTableWidgetItem *detailInfo = new QTableWidgetItem(item[j]);
//              ui->tableWidget->setItem(i,j,detailInfo);
//           }
//       }
 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
}

ViewData::~ViewData()
{
    delete ui;
}

void ViewData::on_data_refresh_clicked()
{
    QList<Product> proList = helper.QgetDate();
    int l = proList.length();
    for(int i = 0; i<l ;i++)//行
    {
        Product pro = proList[i];
        for(int j = 0; j<7 ;j++)//列
        {
            QTableWidgetItem *id = new QTableWidgetItem(pro.id);
            ui->tableWidget->setItem(i,j,id);
            QTableWidgetItem *number = new QTableWidgetItem(pro.number);
            ui->tableWidget->setItem(i,j,number);
            QTableWidgetItem *type = new QTableWidgetItem(pro.type);
            ui->tableWidget->setItem(i,j,type);
            QTableWidgetItem *batchid = new QTableWidgetItem(pro.batchid);
            ui->tableWidget->setItem(i,j,batchid);
            QTableWidgetItem *tray = new QTableWidgetItem(pro.tray);
            ui->tableWidget->setItem(i,j,tray);
            QTableWidgetItem *time = new QTableWidgetItem(pro.time);
            ui->tableWidget->setItem(i,j,time);
            QTableWidgetItem *flag = new QTableWidgetItem(pro.flag);
            ui->tableWidget->setItem(i,j,flag);
        }
    }
}

void ViewData::setWriteability(QList<QTableWidgetItem *> items , bool bl)
{
    bool rdOnly = !bl;
//    item->setFlags((item->flags()) & (~Qt::ItemIsEditable))；
//    for(int i=0; i<items.length(); i++)
//    {
//        items[i]->setFlags((item->flags()) & (~Qt::ItemIsEditable));
//    }
}

void ViewData::on_data_change_clicked()
{
     ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);
     //当前行可写
     QList<QTableWidgetItem *> items = QTableWidget::​selectedItems();//当前选中
     setWriteability(items,true);
     Qres QchangeDate( QString userid,Product oldproduct, Product newproduct);
}

void ViewData::on_data_save_clicked()
{
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ViewData::on_data_add_clicked()
{

}

void ViewData::on_data_delete_clicked()
{
    Qres QdeleteData( QString userid,  Product deleteproduct);
}
