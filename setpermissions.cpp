#include "setpermissions.h"
#include "ui_setpermissions.h"
#include "session.h"
#include "qres.h"
#include "userinfo.h"
#include <QList>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>

//对不同的用户设置不同的权限
SetPermissions::SetPermissions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetPermissions)
{
    ui->setupUi(this);
    Session *curper = Session::getInstance();
    userId = curper->getUserId();
    // 自适应列宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    on_refresh_button_clicked();
}

SetPermissions::~SetPermissions()
{
    delete ui;
}

void SetPermissions::on_change_button_clicked()
{
    //当前行可写
    int row = ui->tableWidget->currentRow();
    if(row != -1)//已选中某行
    {
        UserInfo user_info;
        user_info.userid = ui->tableWidget->item(row,0)->text();
        user_info.username = ui->tableWidget->item(row,1)->text();
        user_info.level = ui->tableWidget->item(row,2)->text();
        cp=new changePermision();
        cp->setUserInfo(user_info);
        if(cp->exec() == QDialog::Accepted)
        {
            on_refresh_button_clicked();
        }
    }else{
        QMessageBox::warning(this,tr("warning"),tr("select one line,please!"));
    }
}

void SetPermissions::on_refresh_button_clicked()
{
    QList<UserInfo> userInfo;
    Qres res = helper.QgetPerson(userInfo,userId);
    if(!res.success)
    {
        QMessageBox::warning(this,tr("warning"),res.msg);
        return;
    }
    int l = userInfo.length();
    ui->tableWidget->setRowCount(l);
    for(int i = 0; i < l; i++)
    {
        QTableWidgetItem *user_id = new QTableWidgetItem(userInfo[i].userid);
        ui->tableWidget->setItem(i,0,user_id);
        QTableWidgetItem *user_name = new QTableWidgetItem(userInfo[i].username);
        ui->tableWidget->setItem(i,1,user_name);
        QTableWidgetItem *user_level = new QTableWidgetItem(userInfo[i].level);
        ui->tableWidget->setItem(i,2,user_level);
    }
}
