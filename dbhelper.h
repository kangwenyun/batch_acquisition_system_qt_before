#ifndef DBHELPER_H
#define DBHELPER_H

#include <QtSql>
#include<qres.h>
#include<qtray.h>
#include<quser.h>
#include<product.h>
#include<QList>

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
    Qres Qchangeuserinformation( QString userid,  Quser newUserinfomation);//不能修改密码和账号
    //about product
    QList<Product>  QgetDate();
    Qres QchangeDate( QString userid,Product oldproduct, Product newproduct);//savedata
    Qres QdeleteData( QString userid,  Product deleteproduct);
    Qres QaddDate( QString userid, Product addproduct);
    Qres QdeleteAllDate(QString userid);
    Qres QgetUserInformation(Quser&  temp,QString userid); //返回的密码是空
    Qres QgetBatchInformation(QString userid,QString Batchid);

    //about Batch
    Qres QaddDataWhileRefreshBatch(Product product);//添加数据的时候刷新batch界面
    Qres QaddBatch(QString batchid,QString batchsum);

    Qres QgetBatchDetialThroughBatchid(QList<Qtray>& list,QString batchid);
private:
    int flag;
    QSqlDatabase db ;
    //help function QaddDataWhileRefreshBatch
    Qres addDate(Product product); //use in QaddDataWhileRefreshBatch
    Qres RefreshBatch(QString batchid);//use in QaddDataWhileRefreshBatch
};

#endif // DBHELPER_H
