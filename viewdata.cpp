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
    ui->tableWidget->setColumnWidth(4,150);
//    // 自适应列宽度
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //select only rows
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //把选中模式设为单选，即每次只选中一行，而不能选中多行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
    on_data_refresh_clicked();
    //定时检查文件并且刷新
    refresh();
    QTimer * timer=new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    timer->start(3000);
}

void ViewData::refresh()
{
    QFile file("Lo1.txt");
    QFileInfo f("Lo1.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    FileData temp;
    temp.time=f.lastModified().toString("yyyy-MM-dd hh:mm:ss");
    if(QString::compare(temp.time,all.time)==0)
    {
       // qDebug()<<"数据没有发生改变";
    }
    else
    {
        qDebug()<<"数据发生了改变";
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            QString str(line);
            temp.data=temp.data+str+"   ";
            temp.line=temp.line+1;
            if(str!=NULL)
            {
                QList<QString> list = line.split(',');
                Product product(list[0],list[1],list[2],list[3],list[4],list[5].toInt());
                helper.QexistOrInsert(product);
            }
        }
        on_data_refresh_clicked();
        all=temp;
        //qDebug()<<all.data;
    }
    file.close();
}
ViewData::~ViewData()
{
    delete ui;
}

void ViewData::on_data_refresh_clicked()
{
    QDateTime time= QDateTime::currentDateTime();
    QList<Product> proList = helper.QgetDatathrouthTime(time.toString("yyyy-MM-dd"));
    int l = proList.length();
    if( l == 0)
    {
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setSpan(0,0,1,6);
        ui->tableWidget->verticalHeader()->setVisible(false);
        QTableWidgetItem *item = new QTableWidgetItem("今天还没有录入任何货物哦~~~");
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
