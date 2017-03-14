#include "maintaindata.h"
#include "ui_maintaindata.h"
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
MaintainData::MaintainData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaintainData)
{
    ui->setupUi(this);
//    // 自适应列宽度
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnWidth(4,150);
    //select only rows
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //把选中模式设为单选，即每次只选中一行，而不能选中多行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(onHeaderClicked(int)));
    pattern = 2;
    //设置时间组建
    QDate d(2017,3,7);
    ui->dateEdit->setMinimumDate(d);
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate());
    on_data_refresh_clicked();
}

MaintainData::~MaintainData()
{
    delete ui;
}

void MaintainData::on_data_refresh_clicked()
{
    QList<Product> proList = helper.QgetData();
    load(proList);
}

void MaintainData::on_data_change_clicked()
{
     //当前行可写
     row = ui->tableWidget->currentRow();
     if(row != -1)//已选中某行
     {
         //批次号,托盘号,货物号,货物类型,录入时间,备注
         bool ok;
         curproduct.batchid = ui->tableWidget->item(row,0)->text();
         curproduct.tray = ui->tableWidget->item(row,1)->text();
         curproduct.number = ui->tableWidget->item(row,2)->text();
         curproduct.type = ui->tableWidget->item(row,3)->text();
         curproduct.time = ui->tableWidget->item(row,4)->text();
         curproduct.flag = ui->tableWidget->item(row,5)->text().toInt(&ok,10);
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

void MaintainData::on_data_add_clicked()
{
    sp=new saveProduct();
    Product pro;
    pro.flag = 0;
    sp->setProduct(pro);
    if(sp->exec() == QDialog::Accepted)
    {
        on_data_refresh_clicked();
    }
}

void MaintainData::on_data_delete_clicked()
{
    //批次号,托盘号,物号,货物类型,录入时间,备注
    row = ui->tableWidget->currentRow() ;//当前行号
    bool ok;
    curproduct.batchid = ui->tableWidget->item(row,0)->text();
    curproduct.tray = ui->tableWidget->item(row,1)->text();
    curproduct.number = ui->tableWidget->item(row,2)->text();
    curproduct.type = ui->tableWidget->item(row,3)->text();
    curproduct.time = ui->tableWidget->item(row,4)->text();
    curproduct.flag = ui->tableWidget->item(row,5)->text().toInt(&ok,10);
    Qres qres;
    switch(QMessageBox::question(this,tr("询问"),tr("确定删除该行数据?"),
                QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
        case QMessageBox::Ok:
            qres = helper.QdeleteData(userId,curproduct);
            if(!qres.success)
            {
                QMessageBox::warning(this,tr("warnig"),qres.msg);
                return;
            }

            on_data_refresh_clicked();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}

void MaintainData::on_data_deleteAll_clicked()
{
    Qres qres;
    switch(QMessageBox::question(this,tr("询问"),tr("确定删除所有数据?"),
                QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
        case QMessageBox::Ok:
            qres = helper.QdeleteAllData(userId);
            if(!qres.success)
            {
                QMessageBox::warning(this,tr("warnig"),qres.msg);
                return;
            }
            on_data_refresh_clicked();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}

void MaintainData::onHeaderClicked(int col)
{
    QString labels[6] = {"批次号","托盘号","货物号","货物类型","录入时间","备注"};
    //按哪个排序就哪个加箭头,其余的删箭头
    int i;
    if(pattern == 1)
    {
        pattern = 2;
        //该表头换成递减图标,其余的还原
        for(i = 0; i < 6; i++)
        {
            if(i != col)
            {
                ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(labels[i]));
            }else{
                ui->tableWidget->setHorizontalHeaderItem(col,new QTableWidgetItem(labels[i] + "  ↓"));
            }
        }

    }else{
        pattern = 1;
        //该表头换成递增图标,其余的还原
        for(i = 0; i < 6; i++)
        {
            if(i != col)
            {
                ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(labels[i]));
            }else{
                ui->tableWidget->setHorizontalHeaderItem(col,new QTableWidgetItem(labels[i] + "  ↑"));
            }
        }
    }
    QList<Product> proList = helper.QgetDataorderby(col,pattern);//0:batchid 1:tray 2:number 3:type 4:time 5:flag      pattern: 1:increase 2: decrease
    load(proList);
}

void MaintainData::load(QList<Product> proList)
{
    int l = proList.length();
    if( l == 0)
    {
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setSpan(0,0,1,6);
        ui->tableWidget->verticalHeader()->setVisible(false);
        QTableWidgetItem *item = new QTableWidgetItem("数据库里还没有录入任何货物哦~~~");
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(0,0,item);
        ui->tableWidget->setShowGrid(false);//隐藏表格线
        return;
    }
    ui->tableWidget->setRowCount(l);
    int j = 0;//列计数
    for(int i = 0; i<l ;i++)//行
    {
        j = 0;
        Product pro = proList[i];
        //批次号,托盘号,货物号,货物类型,录入时间,备注
        QTableWidgetItem *batchid = new QTableWidgetItem(pro.batchid);
        batchid->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,j++,batchid);
        QTableWidgetItem *tray = new QTableWidgetItem(pro.tray);
        tray->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,j++,tray);
        QTableWidgetItem *number = new QTableWidgetItem(pro.number);
        number->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,j++,number);
        QTableWidgetItem *type = new QTableWidgetItem(pro.type);
        type->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,j++,type);
        QTableWidgetItem *time = new QTableWidgetItem(pro.time);
        time->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,j++,time);
        QTableWidgetItem *flag = new QTableWidgetItem(QObject::tr("%1").arg(pro.flag));
        flag->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,j++,flag);
    }
}

void MaintainData::on_dateEdit_userDateChanged(const QDate &date)
{
    QList<Product> proList = helper.QgetDatathrouthTime(date.toString("yyyy-MM-dd"));
    load(proList);
}
