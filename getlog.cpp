#include "getlog.h"
#include "ui_getlog.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QStringList>

//工作日志获得
GetLog::GetLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetLog)
{
    ui->setupUi(this);
    QStringList horizontalheaders;
    horizontalheaders << "shijian" << "zhanghao" << "caozuo";
    ui->tableWidget->setHorizontalHeaderLabels(horizontalheaders); //注意这里是QStringList，QString不行
    ui->tableWidget->setColumnWidth(0,170);
    ui->tableWidget->setColumnWidth(1,70);
    ui->tableWidget->setRowCount(0);
    //加载数据
    QDateTime time = QDateTime::currentDateTime();
    QString fileTime=time.toString("yyyy-MM-dd")+".txt";
    getData(fileTime);
}

GetLog::~GetLog()
{
    delete ui;
}

void GetLog::getData(QString fileTime)
{
    QFile fileIn("Log/"+fileTime);
    if( !fileIn.open(QIODevice::ReadOnly) )
    {
        QMessageBox::warning(this, tr("打开文件"),tr("打开文件失败：") + fileIn.errorString());
        return;
    }
    //文件已经正确打开，定义文本流
    QTextStream tsIn(&fileIn);
    //先清空旧的列表
    ui->tableWidget->clear();
    //加载表格数据
    while( !tsIn.atEnd() )
    {
        //获得数据
        QString line = tsIn.readLine();
        line = line.trimmed();
        QList<QString> list = line.split('^');
        //在表格中插入一行
        int nOldRowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nOldRowCount);
        //添加数据
        QTableWidgetItem *item_0 = new QTableWidgetItem(list.at(0));
        ui->tableWidget->setItem(nOldRowCount,0,item_0);
        QTableWidgetItem *item_1 = new QTableWidgetItem(list.at(1));
        ui->tableWidget->setItem(nOldRowCount,1,item_1);
        QTableWidgetItem *item_2 = new QTableWidgetItem(list.at(2));
        ui->tableWidget->setItem(nOldRowCount,2,item_2);
    }
}
