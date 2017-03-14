#include "addbatch.h"
#include "ui_addbatch.h"
#include "qres.h"
#include "session.h"
#include <QString>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>

addBatch::addBatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBatch)
{
    ui->setupUi(this);
    // 自适应列宽度,隐藏垂直表头
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setRowCount(1);
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
    //将焦点聚集到item[0,0]上
//    ui->tableWidget->itemDoubleClicked(ui->tableWidget->item(0,0));
//    ui->tableWidget->installEventFilter(ui->tableWidget->item(0,0));
    ui->tableWidget->itemEntered(ui->tableWidget->item(0,0));
}

addBatch::~addBatch()
{
    delete ui;
}

void addBatch::on_buttonBox_accepted()
{
    //判断是否有未填项
    for(int i = 0; i < 3; i++)
    {
        if(ui->tableWidget->item(0,i)->text() == NULL)
        {
            QMessageBox::warning(this,tr("warning"),tr("All items are required!"));
            return;
        }
    }
    QString batchid = ui->tableWidget->item(0,0)->text();
    QString batchsum = ui->tableWidget->item(0,1)->text();
    Qres qre = helper.QaddBatch(userId,batchid,batchsum);
    if(!qre.success)
    {
        QMessageBox::warning(this,tr("warning"),qre.msg);
    }
}
