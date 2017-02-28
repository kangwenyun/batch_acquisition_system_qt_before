#include "dbhelper.h"

dbhelper::dbhelper()
{
    flag=0;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Test");
    QcreateProductTable();
    QcreateUserTable();
}


void dbhelper::QcreateProductTable()
{
    if (!db.open()) {
        qDebug() << "Database Error!";
    }
    else  {
        QSqlQuery query;
        query.exec("CREATE TABLE Product("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "number VARCHAR ,"
                   "type VARCHAR,"
                   "batchid VARCHAR,"
                   "tray VARCHAR,"
                   "time  VARCHAR,"
                   "flag  INTEGER)");
    }
}
void  dbhelper::QcreateUserTable()
{
    if (!db.open()) {
        qDebug() << "Database Error!";
    }
    else  {
        QSqlQuery query;
        query.exec("CREATE TABLE User("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "userid VARCHAR,"
                   "username VARCHAR,"
                   "passwd VARCHAR,"
                   "age INT,"
                   "sex BOOL,"
                   "job VARCHAR,"
                   "level INT)");
    }
}
Qres  dbhelper::Qlogin(QString userid,QString passwd)
{
    QSqlQuery query;
    Qres _return;
    query.prepare("select * from User where userid = ?");
    query.addBindValue(userid);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
        _return.error=1;
        _return.success=0;
        _return.msg="database error";
        return _return;
    }
    else
    {
        if(query.next())   //not null
        {
            query.prepare("select * from User where userid = ? and passwd =?");
            query.addBindValue(userid);
            query.addBindValue(passwd);
            if(!query.exec())
            {
                qDebug()<< query.lastError();
                _return.error=1;
                _return.success=0;
                _return.msg="database error";
                return _return;
            }
            else
            {
                if(query.next())
                {
                    _return.error=0;
                    _return.success=1;
                    _return.msg=userid+" login successfully";
                    return _return;
                }
                else
                {
                    _return.error=0;
                    _return.success=0;
                    _return.msg="passwd error";   // passwd error
                    return _return;
                }
            }
        }
        else
        {
            _return.error=0;
            _return.success=false;
            _return.msg="userid error"; //userid error
            return _return;
        }
    }
}
Qres dbhelper::Qregist(Quser u)
{
    Qres _return;
    QSqlQuery query;
    //tes
    QString exist="select * from User where userid= ?  ";
    query.prepare(exist);
    query.addBindValue( u.userid);

    query.exec();
    if(!query.exec())
    {

        qDebug()<<query.lastError();
        _return.error=1;
        _return.msg="database error";
        _return.success=0;
        return _return;
    }
    else
    {
        if(query.next())
        {
            _return.error=0;
            _return.msg="userid has existed";
            _return.success=0;
            return _return;
        }
        else
        {
            QSqlQuery iquery;
            iquery.prepare("insert into User (userid,username,passwd,age,sex,job,level)  values ( ?, ?,?,?,?,?,?)");
            iquery.addBindValue(u.userid);
            iquery.addBindValue(u.username);
            iquery.addBindValue(u.passwd);
            iquery.addBindValue( u.age);
            iquery.addBindValue(u.sex);
            iquery.addBindValue(u.job);
            iquery.addBindValue(u.level);
            iquery.exec();
            db.close();
            _return.error=0;
            _return.msg="success";
            _return.success=1;
            return _return;
        }

    }
}
Qres dbhelper::Qchangepwd(Quser u)
{

}
