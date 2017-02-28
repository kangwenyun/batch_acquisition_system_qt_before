#include "refreshdata.h"
#include "ui_refreshdata.h"
#include<dbhelper.h>
#include<QMessageBox>
//数据实时刷新
RefreshData::RefreshData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RefreshData)
{
    ui->setupUi(this);
 dbhelper db;
 Quser u;
 u.username="A";
 u.userid="B";
 u.age=55;
 u.job="postman";
 u.level=0;
 u.sex=1;
 u.passwd="B";
 db.Qlogin(u);
 QMessageBox::information(this,"",db.Qlogin(u.userid,u.passwd).msg);
    //serverservice service;
  // service.trytoconnect();
// thriftservice service;
//    try
//    {

//   res ress;
//   service.m_client.login(ress,"123","123");
//    }
// catch(apache::thrift::TApplicationException &e)
// {
//     cout<<e.what()<<endl;
// }

}

RefreshData::~RefreshData()
{
    delete ui;
}
