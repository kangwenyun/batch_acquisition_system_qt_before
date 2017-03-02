#ifndef DBHELPER_H
#define DBHELPER_H
#include<quser.h>
#include <QtSql>
#include<qres.h>
#include<product.h>
class dbhelper
{
public:
    dbhelper();
    void QcreateProductTable();
    void QcreateUserTable();
    void QcreateBatchTable();
    Qres Qregist(Quser u);  //注册账号
    Qres Qlogin(QString userid,QString passwd);//登录
    Qres Qchangepwd(QString userid,QString oldpwd,QString newpwd);
    Qres QgetUserrmation(Quser&  temp,QString userid);
    //about product
    Qres Qchangeuserinformation( QString userid,  Quser newUserinfomation);//不能修改密码和账号
    QList<Product>  QgetDate();
    Qres QchangeDate( QString userid,Product oldproduct, Product newproduct);
    Qres QdeleteData( QString userid,  Product deleteproduct);
    Qres QaddDate( QString userid, Product addproduct);
    Qres QdeleteAllDate(QString userid);
    Qres QgetUserInformation(Quser&  temp,QString userid); //返回的密码是空
    Qres QgetBatchInformation(QString userid,QString Batchid);

    //about Batch
    Qres QaddDataWhileRefreshBatch(Product product);
    Qres QaddBatch(QString batchid,QString batchsum);
    Qres QdeleteBatchTable();

private:
    int flag;
    QSqlDatabase db ;
    Qres addDate(Product product); //use in QaddDataWhileRefreshBatch
    Qres RefreshBatch(QString batchid);//use in QaddDataWhileRefreshBatch
};

#endif // DBHELPER_H
