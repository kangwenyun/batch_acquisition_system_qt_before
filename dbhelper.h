#ifndef DBHELPER_H
#define DBHELPER_H

#include <QtSql>
#include<qres.h>
#include<qtray.h>
#include<quser.h>
#include<product.h>
#include<QList>
#include<filedata.h>
#include<qbatch.h>
class dbhelper
{
public:
    dbhelper();
    //initdb
    void deleteall();
    void initdb();
    void QdeleteBatchTable();
    void QdeleteProductTable();
    void QdeleteUserTable();
    //
    void QcreateProductTable();
    void QcreateUserTable();
    void QcreateBatchTable();
    Qres Qregist(Quser u);  //注册账号
    Qres Qlogin(QString userid,QString passwd);//登录
    Qres Qchangepwd(QString userid,QString oldpwd,QString newpwd);
    Qres QgetUserrmation(Quser&  temp,QString userid);
    //about product
    Qres Qchangeuserinformation( QString userid,  Quser newUserinfomation);//不能修改密码和账号
    QList<Product>  QgetData();
    Qres QchangeData( QString userid,Product oldproduct, Product newproduct);
    Qres QdeleteData( QString userid,  Product deleteproduct);
    Qres QaddData( QString userid, Product addproduct);
    Qres QdeleteAllData(QString userid);
    Qres QgetUserInformation(Quser&  temp,QString userid); //返回的密码是空
    Qres QgetBatchInformation(QString userid,QString Batchid);

    //about Batch
    Qres QaddDataWhileRefreshBatch(QString userid ,Product product);
    Qres QaddBatch(QString userid,QString batchid,QString batchsum);
    Qres QgetBatchDetialThroughBatchid(QList<Qtray>& list,QString batchid);

    //about refreshdata
    Qres QexistOrInsert(Product product);
    Qres Qrefreshfile();
    QList<Qbatch> QgetBatch();
private:
    int flag;
    QSqlDatabase db ;
    //help function QaddDataWhileRefreshBatch
    Qres addData(Product product); //use in QaddDataWhileRefreshBatch
    Qres RefreshBatch(QString batchid);//use in QaddDataWhileRefreshBatch
};

#endif // DBHELPER_H
