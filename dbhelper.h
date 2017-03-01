#ifndef DBHELPER_H
#define DBHELPER_H
#include <quser.h>
#include <QtSql>
#include <qres.h>
#include <product.h>
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
    Qres Qchangeuserinformation( Quser olduserinformation,  Quser newUserinfomation);
    QList<Product>  QgetDate();
    Qres QchangeDate( QString userid,Product oldproduct, Product newproduct);
    Qres QdeleteData( QString userid,  Product deleteproduct);
    Qres QaddDate( QString userid, Product addproduct);
    Qres QdeleteAllDate(QString userid);
private:
    int flag;
    QSqlDatabase db ;
};

#endif // DBHELPER_H
