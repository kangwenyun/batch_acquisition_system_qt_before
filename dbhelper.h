#ifndef DBHELPER_H
#define DBHELPER_H
#include<quser.h>
#include <QtSql>
#include<qres.h>
class dbhelper
{
public:
    dbhelper();
    void QcreateProductTable();
    void QcreateUserTable();
    Qres Qregist(Quser u);
    Qres Qlogin(QString userid,QString passwd);
    Qres Qchangepwd(Quser u);
private:
    int flag;
    QSqlDatabase db ;
};

#endif // DBHELPER_H
