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
            query.prepare("select * from User where userid = :userid and passwd = :passwd");
            query.bindValue(":userid",userid);
            query.bindValue(":passwd",passwd);
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
            iquery.prepare("insert into User (userid,username,passwd,age,sex,job,level)  values ( :userid,:username,:passwd,:age,:sex,:job,:level)");
            iquery.bindValue(":userid",u.userid);
            iquery.bindValue(":username",u.username);
            iquery.bindValue(":passwd",u.passwd);
            iquery.bindValue(":age", u.age);
            iquery.bindValue(":sex",u.sex);
            iquery.bindValue(":job",u.job);
            iquery.bindValue(":level",u.level);
            iquery.exec();
            db.close();
            _return.error=0;
            _return.msg="success";
            _return.success=1;
            return _return;
        }

    }
}
Qres dbhelper::Qchangepwd(QString userid,QString oldpwd,QString newpwd)
{
    Qres _return;
    QSqlQuery query;
    query.prepare("select * from User where userid=? and passwd = ?");
    query.addBindValue(userid);
    query.addBindValue(oldpwd);
    if(!query.exec())
    {
        qDebug()<<"database error";
        _return.error=1;
        _return.success=false;
        _return.msg="database error";
    }
    else
    {
        if(query.next())
        {
            QSqlQuery updatequery;
            updatequery.prepare("update User set passwd = ? where userid = ?");
            updatequery.addBindValue(newpwd);
            updatequery.addBindValue(userid);
            if(updatequery.exec())
            {
                _return.error=0;
                _return.msg="change password successfully";
                _return.success=true;
                return _return;
            }
            else
            {
                _return.error=1;
                _return.msg="datebase error";
                _return.success=false;
                return _return;
            }
        }
        else
        {
            _return.error=0;
            _return.success=false;
            _return.msg="passwd error";
            return _return;
        }
    }
}



Qres dbhelper::Qchangeuserinformation( Quser olduserinformation,  Quser newUserinfomation)
{

}

QList<Product>  dbhelper::QgetDate()
{
    QList<Product> list;
    QSqlQuery sql_query;
    QString select_sql = "select * from product";
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<"error";
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            Product temp;

            temp.id = sql_query.value("id").toInt();
            temp.number=sql_query.value("number").toString();
            qDebug()<<temp.number;
            temp.type=sql_query.value("type").toString();
            temp.batchid=sql_query.value("batchid").toString();
            temp.tray=sql_query.value("tray").toString();
            temp.time=sql_query.value("time").toString();
            temp.flag=sql_query.value("flag").toInt();
            list.append(temp);
            // number=? , type=?  , batchid=? , tray=? , time=? , flag=?
            // QString name = sql_query.value("name").toString();

        }
        return list;
    }
}

Qres dbhelper::QchangeDate( QString userid,Product oldproduct, Product newproduct)
{
    Qres _return;
    QSqlQuery uquery;
    QSqlQuery query;
    uquery.prepare("select * from user where userid= ?");
    uquery.addBindValue(userid);
    uquery.exec();
    if(uquery.next())
    {
        if(uquery.value("level").toInt()==0)
        {
            query.prepare("update product set number=? , type=?  , batchid=? , tray=? , time=? , flag=?  where number = ? and tray=? and  time =?");
            query.addBindValue(newproduct.number);
            query.addBindValue(newproduct.type);
            query.addBindValue(newproduct.batchid);
            query.addBindValue(newproduct.tray);
            query.addBindValue(newproduct.time);
            query.addBindValue(newproduct.flag);
            query.addBindValue(oldproduct.number);
            query.addBindValue(oldproduct.tray);
            query.addBindValue(oldproduct.time);

            if(query.exec())
            {
                qDebug()<<"update";
                _return.error=0;
                _return.msg="updatesuccess";
                _return.success=1;
                return _return;
            }
            else
            {

                _return.error=1;
                _return.msg="database error";
                _return.success=0;
                return _return;
            }
        }
        else
        {
            _return.error=0;
            _return.msg="user level is not enough";
            _return.success=0;
            return _return;
        }
    }
    else
    {
        _return.error=0;
        _return.msg="userid is error";
        _return.success=0;
        return _return;
    }
}

Qres dbhelper::QdeleteData( QString userid,  Product deleteproduct)
{
    Qres _return;
    QSqlQuery uquery;
    QSqlQuery query;
    uquery.prepare("select * from user where userid= ?");
    uquery.addBindValue(userid);
    uquery.exec();
    if(uquery.next())
    {
        if(uquery.value("level").toInt()==0)
        {
            // query.prepare("delete  from product where id = ?");
            //query.addBindValue((int)deleteproduct.id);

            //
            //
            //
            //这里需要修改
            query.prepare("delete   from product where number=?");
            query.addBindValue(deleteproduct.number);
            if(query.exec())
            {
                qDebug()<<"deleted!";
                _return.error=0;
                _return.msg="deletesuccess";
                _return.success=1;
                return _return;
            }
            else
            {

                _return.error=1;
                _return.msg="database error";
                _return.success=0;
                return _return;
            }
        }
        else
        {
            _return.error=0;
            _return.msg="user level is not enough";
            _return.success=0;
            return _return;
        }
    }
    else
    {
        _return.error=0;
        _return.msg="userid is error";
        _return.success=0;
        return _return;
    }
}

Qres dbhelper::QaddDate( QString userid, Product addproduct)
{
    Qres _return;
    QSqlQuery query;
    //    query.prepare("insert into product (number,type,batchid,tray,time,flag)  values ( ?, ?,?,?,?,?)");
    //    query.addBindValue(addproduct.number);
    //    query.addBindValue(addproduct.type);
    //    query.addBindValue(addproduct.batchid);
    //    query.addBindValue(addproduct.tray);
    //    query.addBindValue(addproduct.time);
    //    query.addBindValue(addproduct.flag);
    query.prepare("insert into product (number,type,batchid,tray,time,flag)  values ( :number,:type,:batchid,:tray,:time,:flag)");
    query.bindValue(":number",addproduct.number);
    query.bindValue(":type",addproduct.type);
    query.bindValue(":batchid",addproduct.batchid);
    query.bindValue(":tray",addproduct.tray);
    query.bindValue(":time",addproduct.time);
    query.bindValue(":flag",addproduct.flag);

    if(query.exec())
    {
        qDebug()<<"success insert";
        _return.error=0;
        _return.msg="success insert the product ";
        _return.success=1;
        return _return;
    }
    else
    {
        qDebug()<<"failed insert";
        _return.error=1;
        _return.msg="database error";
        _return.success=0;
        return _return;
    }

}
Qres dbhelper::QdeleteAllDate(QString userid)
{
    Qres _return;
    QSqlQuery query;
    query.prepare("select level from user where userid = ?");
    query.addBindValue(userid);
    if(query.exec())
    {
        if(query.next())
        {
            if(query.value(0).toInt()==0)
            {
                QSqlQuery dquery;
                dquery.exec("delete from product");
                _return.error=0;
                _return.msg="clear success";
                _return.success=true;
            }
            else
            {
                _return.error=0;
                _return.msg="权限不够";
                _return.success=false;
            }

        }
        else
        {
            _return.error=0;
            _return.msg="账号不存在";
            _return.success=false;
        }
        return _return;
    }
    else
    {
        qDebug()<<"false";
        return  _return;
    }
}
