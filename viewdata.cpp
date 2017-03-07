#include "viewdata.h"
#include "ui_viewdata.h"
#include "dbhelper.h"
#include "product.h"
#include "session.h"
#include <QList>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>
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
    //把选中模式设为单选，即每次只选中一行，而不能选中多行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
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
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
}

void ViewData::setWriteability(int row , bool bl)
{
    if(bl)
    {
        ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);//所有可写
        //非选中行均设置为不可写
        QTableWidgetItem *item;
        int i = 0;
        for(; i < row; i++)
        {
            for(int j=0; j<7; j++)
            {
                item = ui->tableWidget->item(i,j);
                item->setFlags(Qt::NoItemFlags);
            }
        }
        i++;
        item = ui->tableWidget->item(row,0);
        if(item != NULL)
        {
            item->setFlags(Qt::NoItemFlags);
        }
        for(; i >row && i < ui->tableWidget->rowCount(); i++)
        {
            for(int j=0; j<7; j++)
            {
                item = ui->tableWidget->item(i,j);
                item->setFlags(Qt::NoItemFlags);
            }
        }
    }else{
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    }
}

void ViewData::on_data_change_clicked()
{
     //当前行可写
     row = ui->tableWidget->currentRow();
     if(row != -1)//已选中某行
     {
         bool ok;
         curproduct.id = ui->tableWidget->item(row,0)->text().toInt(&ok,10);
         curproduct.number = ui->tableWidget->item(row,1)->text();
         curproduct.type = ui->tableWidget->item(row,2)->text();
         curproduct.batchid = ui->tableWidget->item(row,3)->text();
         curproduct.tray = ui->tableWidget->item(row,4)->text();
         curproduct.time = ui->tableWidget->item(row,5)->text();
         curproduct.flag = ui->tableWidget->item(row,6)->text().toInt(&ok,10);
         sp=new saveProduct();
         sp->setProduct(curproduct);
         if(sp->exec() == QDialog::Accepted)
         {
             on_data_refresh_clicked();
         }
     }else{
         QMessageBox::warning(this,tr("warning"),tr("select one line,please!"));
     }
}

void ViewData::on_data_add_clicked()
{
    //获取旧的行计数，表格末尾加入一个新空行，有新的空行才能设置新行条目
//    int nOldRowCount = ui->tableWidget->rowCount();
//    ui->tableWidget->insertRow(nOldRowCount);
//    setWriteability(nOldRowCount,true);
//    Product addproduct;
//    bool ok;
//    addproduct.number = ui->tableWidget->item(nOldRowCount,1)->text().toInt(&ok,10);
//    addproduct.type = ui->tableWidget->item(nOldRowCount,2)->text();
//    addproduct.batchid = ui->tableWidget->item(nOldRowCount,3)->text();
//    addproduct.tray = ui->tableWidget->item(nOldRowCount,4)->text();
//    addproduct.time = ui->tableWidget->item(nOldRowCount,5)->text();
//    addproduct.flag = ui->tableWidget->item(nOldRowCount,6)->text().toInt(&ok,10);
//    Qres qres = helper.QaddData(userId, addproduct);
//    if(!qres.success)
//    {
//        QMessageBox::warning(this,tr("warning"),qres.msg);
//    }
    sp=new saveProduct();
    Product pro;
    pro.flag = 0;
    sp->setProduct(pro);
    if(sp->exec() == QDialog::Accepted)
    {
        on_data_refresh_clicked();
    }
}

void ViewData::on_data_delete_clicked()
{
    row = ui->tableWidget->currentRow() ;//当前行号
    bool ok;
    curproduct.number = ui->tableWidget->item(row,1)->text().toInt(&ok,10);
    curproduct.type = ui->tableWidget->item(row,2)->text();
    curproduct.batchid = ui->tableWidget->item(row,3)->text();
    curproduct.tray = ui->tableWidget->item(row,4)->text();
    curproduct.time = ui->tableWidget->item(row,5)->text();
    curproduct.flag = ui->tableWidget->item(row,6)->text().toInt(&ok,10);
    Qres qres;
    switch(QMessageBox::question(this,tr("询问"),tr("确定删除?"),
                QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
        case QMessageBox::Ok:
            ui->tableWidget->removeRow(row);
            qres = helper.QdeleteData(userId,curproduct);
            if(!qres.success)
            {
                QMessageBox::warning(this,tr("warnig"),qres.msg);
            }
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}
