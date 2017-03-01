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
    Qres Qregist(Quser u);
    Qres Qlogin(QString userid,QString passwd);
    Qres Qchangepwd(QString userid,QString oldpwd,QString newpwd);
    //about product
    Qres changeuserinformation( Quser olduserinformation,  Quser newUserinfomation);
    QList<Product>  getDate();
    Qres changeDate( QString userid,Product oldproduct, Product newproduct);
    Qres deleteData( QString userid,  Product deleteproduct);
    Qres addDate( QString userid, Product addproduct);
private:
    int flag;
    QSqlDatabase db ;
};

#endif // DBHELPER_H
