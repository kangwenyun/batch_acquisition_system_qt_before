#include "dbhelper.h"
#include<loger.h>
dbhelper::dbhelper()
{

    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Test");
    QcreateProductTable();
    QcreateUserTable();
    QcreateBatchTable();

}

void dbhelper::QcreateBatchTable()
{
    if (!db.open()) {
        qDebug() << "Database Error!";
    }
    else  {
        QSqlQuery query;
        query.exec("CREATE TABLE Batch("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "batchid VARCHAR ,"
                   "batchsum VARCHAR,"
                   "batchamout VARCHAR)");
    }

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
                   "age VARCHAR,"
                   "sex VARCHAR,"
                   "job VARCHAR,"
                   "level VARCHAR)");
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
        _return.msg="登录时发生了数据库错误";
        Loger::getInstance()->setLoger(userid,_return.msg);
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
                _return.msg="登录时发生了数据库错误";
                Loger::getInstance()->setLoger(userid,_return.msg);
                return _return;
            }
            else
            {
                if(query.next())
                {
                    _return.error=0;
                    _return.success=1;
                    _return.msg="登录成功";
                    Loger::getInstance()->setLoger(userid,_return.msg);
                    return _return;
                }
                else
                {
                    _return.error=0;
                    _return.success=0;
                    _return.msg="登录时密码错误";   // passwd error
                    Loger::getInstance()->setLoger(userid,_return.msg);
                    return _return;
                }
            }
        }
        else
        {
            _return.error=0;
            _return.success=false;
            _return.msg="登录时账号错误"; //userid error
            Loger::getInstance()->setLoger(userid,_return.msg);
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
        _return.msg="注册时发生数据库错误";
        _return.success=0;
        Loger::getInstance()->setLoger(u.userid,_return.msg);
        return _return;
    }
    else
    {
        if(query.next())
        {
            _return.error=0;
            _return.msg="账号已经存在";
            _return.success=0;
            Loger::getInstance()->setLoger(u.userid,_return.msg);
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
            _return.error=0;
            _return.msg="注册成功";
            _return.success=1;
            Loger::getInstance()->setLoger(u.userid,_return.msg);
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

        _return.error=1;
        _return.success=false;
        _return.msg="修改密码时发生数据库错误";
        Loger::getInstance()->setLoger(userid,_return.msg);
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
                _return.msg="修改密码成功";
                _return.success=true;
                Loger::getInstance()->setLoger(userid,_return.msg);
                return _return;
            }
            else
            {
                _return.error=1;
                _return.msg="修改密码时发生数据库错误";
                _return.success=false;
                Loger::getInstance()->setLoger(userid,_return.msg);
                return _return;
            }
        }
        else
        {
            _return.error=0;
            _return.success=false;
            _return.msg="修改密码时原密码错误";
            Loger::getInstance()->setLoger(userid,_return.msg);
            return _return;
        }
    }
}

Qres dbhelper::Qchangeuserinformation( QString userid,  Quser newUserinfomation)
{
    QSqlQuery query;
    Qres  _return;
    query.prepare("update User set age=:age , job=:job  , level=:level , sex=:sex ,username=:username  where userid= :userid");
    query.bindValue(":age",newUserinfomation.age);
    query.bindValue(":job",newUserinfomation.job);
    query.bindValue(":level",newUserinfomation.level);
    query.bindValue(":sex",newUserinfomation.sex);
    query.bindValue(":username",newUserinfomation.username);
    query.bindValue(":userid",userid);

    if(query.exec())
    {
        _return.error=0;
        _return.msg="修改用户信息成功";
        _return.success=1;
        Loger::getInstance()->setLoger(userid,_return.msg);
        return _return;
    }
    else
    {
        _return.error=1;
        _return.msg="修改用户信息时发生数据库错误";
        _return.success=0;
        Loger::getInstance()->setLoger(userid,_return.msg);
        return _return;
    }
}

QList<Product>  dbhelper::QgetData()
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

Qres dbhelper::QchangeData( QString userid,Product oldproduct, Product newproduct)
{
    Qres _return;
    QSqlQuery uquery;
    QSqlQuery query;
    uquery.prepare("select * from user where userid= ?");
    uquery.addBindValue(userid);
    uquery.exec();
    if(uquery.next())
    {
        if(uquery.value("level").toString()=="0")
        {
            query.prepare("update product set number=? , type=?  , batchid=? , tray=? , time=? , flag=?  where batchid =? and number = ? and tray=? and  time =?");
            query.addBindValue(newproduct.number);
            query.addBindValue(newproduct.type);
            query.addBindValue(newproduct.batchid);
            query.addBindValue(newproduct.tray);
            query.addBindValue(newproduct.time);
            query.addBindValue(newproduct.flag);
            query.addBindValue(oldproduct.batchid);
            query.addBindValue(oldproduct.number);
            query.addBindValue(oldproduct.tray);
            query.addBindValue(oldproduct.time);

            if(query.exec())
            {
                qDebug()<<"update";
                _return.error=0;
                _return.msg="修改了货物信息,旧的批次号:"+oldproduct.batchid+" 旧的托盘号为:"+oldproduct.tray+" 旧的序号为:"+oldproduct.number+" 新的批次号:"+newproduct.batchid+" 新的托盘号为:"+newproduct.tray+" 新的序号为:"+newproduct.number;
                _return.success=1;
                Loger::getInstance()->setLoger(userid,_return.msg);
                return _return;
            }
            else
            {

                _return.error=1;
                _return.msg="修改货物信息时发生数据库错误";
                _return.success=0;
                Loger::getInstance()->setLoger(userid,_return.msg);
                return _return;
            }
        }
        else
        {
            _return.error=0;
            _return.msg="修改货物信息的权限不够";
            _return.success=0;
            Loger::getInstance()->setLoger(userid,_return.msg);
            return _return;
        }
    }
    else
    {
        _return.error=0;
        _return.msg="账号错误";
        _return.success=0;
        Loger::getInstance()->setLoger(userid,_return.msg);
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
        if(uquery.value("level").toString()=="0")
        {
            // query.prepare("delete  from product where id = ?");
            //query.addBindValue((int)deleteproduct.id);

            //
            //
            //
            //这里需要修改
            query.prepare("delete   from product where number=? and tray=? and batchid=?");
            query.addBindValue(deleteproduct.number);
            query.addBindValue(deleteproduct.tray);
            query.addBindValue(deleteproduct.batchid);
            if(query.exec())
            {
                _return.error=0;
                _return.msg="删除货物成功,货物序号:"+deleteproduct.number+" 货物托盘号:"+deleteproduct.tray+" 货物批次号:"+deleteproduct.batchid;
                _return.success=1;
                Loger::getInstance()->setLoger(userid,_return.msg);
                return _return;
            }
            else
            {

                _return.error=1;
                _return.msg="删除货物时发生数据库错误";
                _return.success=0;
                Loger::getInstance()->setLoger(userid,_return.msg);
                return _return;
            }
        }
        else
        {
            _return.error=0;
            _return.msg="用户权限不足,无法删除数据";
            _return.success=0;
            Loger::getInstance()->setLoger(userid,_return.msg);
            return _return;
        }
    }
    else
    {
        _return.error=0;
        _return.msg="账号错误";
        _return.success=0;
        Loger::getInstance()->setLoger(userid,_return.msg);
        return _return;
    }
}

Qres dbhelper::QaddData( QString userid, Product addproduct)
{
    Qres _return;
    QSqlQuery query;
    query.prepare("insert into product (number,type,batchid,tray,time,flag)  values ( :number,:type,:batchid,:tray,:time,:flag)");
    query.bindValue(":number",addproduct.number);
    query.bindValue(":type",addproduct.type);
    query.bindValue(":batchid",addproduct.batchid);
    query.bindValue(":tray",addproduct.tray);
    QDateTime  time=QDateTime::currentDateTime();
    QString current=time.toString("yyyy-MM-dd hh:mm:ss");
    query.bindValue(":time",current);
    //query.bindValue(":time",addproduct.time);
    query.bindValue(":flag",addproduct.flag);

    if(query.exec())
    {
        qDebug()<<"success insert";
        _return.error=0;
        _return.msg="成功上传数据,批次号:"+addproduct.batchid+" 托盘号为:"+addproduct.tray+" 序号为:"+addproduct.number;
        _return.success=1;
        Loger::getInstance()->setLoger(userid,_return.msg);
        return _return;
    }
    else
    {
        qDebug()<<"failed insert";
        _return.error=1;
        _return.msg="上传数据时发生数据库错误";
        _return.success=0;
        Loger::getInstance()->setLoger(userid,_return.msg);
        return _return;
    }

}

Qres dbhelper::QdeleteAllData(QString userid)
{
    Qres _return;
    QSqlQuery query;
    query.prepare("select level from user where userid = ?");
    query.addBindValue(userid);
    if(query.exec())
    {
        if(query.next())
        {
            if(query.value(0).toString()=="0")
            {
                QSqlQuery dquery;
                dquery.exec("delete from product");
                _return.error=0;
                _return.msg="删除所有数据成功";
                _return.success=true;
                Loger::getInstance()->setLoger(userid,_return.msg);
            }
            else
            {
                _return.error=0;
                _return.msg="权限不够";
                _return.success=false;
                Loger::getInstance()->setLoger(userid,_return.msg);
            }

        }
        else
        {
            _return.error=0;
            _return.msg="账号不存在";
            _return.success=false;
            Loger::getInstance()->setLoger(userid,_return.msg);
        }
        return _return;
    }
    else
    {
        _return.error=1;
        _return.msg="删除所有数据,发生数据库错误";
        _return.success=0;
        Loger::getInstance()->setLoger(userid,_return.msg);
        return  _return;
    }
}


QList<Product> dbhelper::QgetDatathrouthTime(QString time)
{
    QSqlQuery query;
    QList<Product> list;
    //"select * from Product where time  like  '%2017-03-09%'"
    QString searchtime="select * from Product where time  like  '%"+time+"%'";
    if(query.exec(searchtime))
    {
        while(query.next())
        {
            Product temp;
            temp.number=query.value("number").toString();
            temp.type=query.value("type").toString();
            temp.batchid=query.value("batchid").toString();
            temp.tray=query.value("tray").toString();
            temp.time=query.value("time").toString();
            temp.flag=query.value("flag").toInt();
            list.append(temp);
        }
        return list;
    }
    else
    {
        return list;
    }
    return list;
}

Qres dbhelper::QgetUserrmation(Quser&  temp,QString userid)
{
    Qres _return;
    QSqlQuery query;
    query.prepare("select * from user where userid=?");
    query.addBindValue(userid);
    if(query.exec())
    {
        if(query.next())
        {
            temp.userid=query.value("userid").toString();
            temp.age=query.value("age").toString();
            temp.job=query.value("job").toString();
            temp.level=query.value("level").toString();
            temp.passwd="";
            temp.sex=query.value("sex").toString();
            temp.username=query.value("username").toString();

            _return.error=0;
            _return.msg="获得个人信息成功";
            _return.success=1;
            Loger::getInstance()->setLoger(userid,_return.msg);

        }
        else
        {

            _return.error=0;
            _return.msg="获得个人信息失败";
            _return.success=0;
            Loger::getInstance()->setLoger(userid,_return.msg);
        }
    }
    else
    {

        _return.error=1;
        _return.msg="获得个人信息时发生数据库错误";
        _return.success=0;
        Loger::getInstance()->setLoger(userid,_return.msg);
    }
    return _return;
}

Qres dbhelper::QaddBatch(QString userid,QString batchid,QString batchsum)
{
    Qres _return;
    QSqlQuery squery;
    squery.prepare("select * from Batch where batchid=?");
    squery.addBindValue(batchid);
    if(squery.exec())
    {
        if(squery.next())
        {
            _return.error=0;
            _return.msg="批次号已经存在无法添加";
            _return.success=0;
            Loger::getInstance()->setLoger(userid,_return.msg);
        }
        else
        {
            QSqlQuery query;
            query.prepare("insert into Batch  (batchid,batchsum,batchamout)  values ( :batchid,:batchsum,:batchamout)");
            query.bindValue(":batchid",batchid);
            query.bindValue(":batchsum",batchsum);
            query.bindValue(":batchamout","0");
            if(query.exec())
            {
                _return.error=0;
                _return.msg="添加批次号成功,批次号为"+batchid;
                _return.success=1;
                Loger::getInstance()->setLoger(userid,_return.msg);
            }
            else
            {
                _return.error=1;
                _return.msg="添加批次时发成数据库错误";
                _return.success=0;
                Loger::getInstance()->setLoger(userid,_return.msg);
            }
        }
    }
    else
    {
        _return.error=1;
        _return.msg="添加批次时发成数据库错误";
        _return.success=0;
        Loger::getInstance()->setLoger(userid,_return.msg);
    }
    return _return;


}

Qres dbhelper::QaddDataWhileRefreshBatch(QString userid,Product product)
{
    Qres _return;
    Qres refresh;
    Qres add;
    QString batchid=product.batchid;
    QSqlQuery query;
    query.prepare("select * from Batch where batchid = ?");
    query.addBindValue(batchid);
    if(query.exec())
    {
        if(query.next())
        {
            //exist batch then insert into Product and update Batch
            add=addData(product);
            if(add.success==1)
            {
                refresh=RefreshBatch(batchid);
                if(refresh.success==1)
                {
                    _return.error=0;
                    _return.msg="添加新货物并且刷新批次成功,货物信息批次号:"+product.batchid+" 序号:"+product.number+" 托盘号"+product.number;
                    _return.success=1;
                    Loger::getInstance()->setLoger(userid,_return.msg);
                }
                else
                {
                    _return.error=refresh.error;
                    _return.msg=refresh.msg;
                    _return.success=refresh.success;
                    Loger::getInstance()->setLoger(userid,_return.msg);
                }
            }
            else
            {
                _return.error=add.error;
                _return.msg=add.msg;
                _return.success=add.success;
                Loger::getInstance()->setLoger(userid,_return.msg);
            }
        }
        else
        {
            product.flag=1;
            addData(product);
            _return.error=0;
            _return.msg="不存在该批次号,数据加入数据库中但是错误标记为1";
            _return.success=1;
            Loger::getInstance()->setLoger(userid,_return.msg);
        }
    }
    else
    {
        //database error
        _return.error=1;
        _return.msg="发生了数据库错误";
        _return.success=0;
        Loger::getInstance()->setLoger(userid,_return.msg);
    }
    return _return;
}

Qres dbhelper::addData(Product product)
{
    Qres _return;
    QSqlQuery query;
    query.prepare("insert into product (number,type,batchid,tray,time,flag)  values ( :number,:type,:batchid,:tray,:time,:flag)");
    query.bindValue(":number",product.number);
    query.bindValue(":type",product.type);
    query.bindValue(":batchid",product.batchid);
    query.bindValue(":tray",product.tray);
    QString current;
    if(product.time=="now")
    {
        QDateTime  time=QDateTime::currentDateTime();
        current=time.toString("yyyy-MM-dd hh:mm:ss");
        qDebug()<<"now time";
    }
    else
    {
        current=product.time;
        qDebug()<<"product time";
    }
    query.bindValue(":time",current);
    query.bindValue(":flag",product.flag);
    if(query.exec())
    {
        qDebug()<<"success insert";
        _return.error=0;
        _return.msg="成功加入数据";
        _return.success=1;
        return _return;
    }
    else
    {
        qDebug()<<"failed insert";
        _return.error=1;
        _return.msg="加入数据时发生数据库错误";
        _return.success=0;
        return _return;
    }
}

Qres dbhelper::RefreshBatch(QString batchid)
{
    Qres _return;
    QSqlQuery query;
    query.prepare("select batchamout from Batch where batchid=?");
    query.addBindValue(batchid);
    if(query.exec())
    {
        if(query.next())
        {
            int amout= query.value(0).toInt()+1;
            QString batchamout= QString::number(amout);
            QSqlQuery updatequery;
            updatequery.prepare("update Batch set batchamout = ? where batchid=?");
            updatequery.addBindValue(batchamout);
            updatequery.addBindValue(batchid);
            if(updatequery.exec())
            {
                //update success
                _return.error=0;
                _return.msg="刷新批次成功,批次号为:"+batchid;
                _return.success=1;
            }
            else
            {
                //data base error
                _return.error=1;
                _return.msg="刷新批次号时发生数据库错误";
                _return.success=0;
            }
        }
        else
        {
            //not exist batchid
            _return.error=0;
            _return.msg="刷新批次号时发现不存在该批次号";
            _return.success=0;
        }
    }
    else
    {
        //database error
        _return.error=1;
        _return.msg="刷新批次号时候发生数据库错误";
        _return.success=0;
    }
    return _return;
}

void dbhelper::QdeleteBatchTable()
{
    QSqlQuery query;
    query.prepare("delete from Batch ");
    if(query.exec())
    {
        qDebug()<<"success";
    }
    else
    {
        qDebug()<<"fail";
    }
}
void dbhelper::QdeleteProductTable()
{
    QSqlQuery query;
    query.prepare("delete from Product ");
    if(query.exec())
    {
        qDebug()<<"success";

    }
    else
    {
        qDebug()<<"fail";
    }
}
void dbhelper::QdeleteUserTable()
{
    QSqlQuery query;
    query.prepare("delete from User where userid ");
    if(query.exec())
    {
        qDebug()<<"success";
    }
    else
    {
        qDebug()<<"fail";
    }
}

Qres dbhelper::QgetBatchDetialThroughBatchid(QList<Qtray>& list,QString batchid)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Test");
    QcreateProductTable();
    QcreateUserTable();
    QcreateBatchTable();
    Qres _return;
    QSqlQuery query;
    query.prepare("select distinct tray from Product where batchid = ?");
    query.addBindValue(batchid);
    if(query.exec())
    {
        while(query.next())
        {
            Qtray temp;
            temp.tray=query.value(0).toString();
            QSqlQuery squery;
            squery.prepare("select * from product where tray=? and batchid=?");
            squery.addBindValue(temp.tray);
            squery.addBindValue(batchid);
            if(squery.exec())
            {
                while(squery.next())
                {
                    Product tempproduct;
                    tempproduct.batchid=batchid;
                    tempproduct.flag=squery.value("flag").toInt();
                    tempproduct.number=squery.value("number").toString();
                    tempproduct.time=squery.value("time").toString();
                    tempproduct.tray=squery.value("tray").toString();
                    tempproduct.type=squery.value("type").toString();
                    temp.productlist.append(tempproduct);
                }
            }
            else
            {
                //database error
                _return.error=1;
                _return.msg="数据库错误";
                _return.success=0;
            }
            list.append(temp);
        }
        _return.error=0;
        _return.msg="getBactchDetial successfully";
        _return.success=1;
    }
    else
    {
        //databaseerror
        _return.error=1;
        _return.msg="数据库错误";
        _return.success=0;
    }
    return _return;
}
void dbhelper::deleteall()
{
    QdeleteBatchTable();
    QdeleteUserTable();
    QdeleteProductTable();
}

void dbhelper::initdb()
{

    Quser admin("admin","admin","admin","30","man","postman","0");
    Quser user("user","user","user","30","man","postman","1");
    Qregist(admin);
    Qregist(user);
    QaddBatch("admin","A1","50");
    QaddBatch("admin","A2","60");
    QaddBatch("admin","A3","40");
    QaddBatch("admin","A4","30");
    Product A1product1("1","A","A1","T1","now",0);
    Product A1product2("2","A","A1","T1","now",0);
    Product A1product3("3","A","A1","T1","now",0);
    Product A1product4("4","A","A1","T2","now",0);
    Product A1product5("5","A","A1","T2","now",0);
    Product A1product6("6","A","A1","T2","now",0);
    Product A1product7("7","A","A1","T3","now",0);

    Product A2product1("1","A","A2","T1","now",0);
    Product A2product2("2","A","A2","T1","now",0);
    Product A2product3("3","A","A2","T1","now",0);
    Product A2product4("4","A","A2","T2","now",0);
    Product A2product5("5","A","A2","T2","now",0);
    Product A2product6("6","A","A2","T2","now",0);
    Product A2product7("7","A","A2","T3","now",0);

    Product A3product1("1","A","A3","T1","now",0);
    Product A3product2("2","A","A3","T1","now",0);
    Product A3product3("3","A","A3","T1","now",0);
    Product A3product4("4","A","A3","T2","now",0);
    Product A3product5("5","A","A3","T2","now",0);
    Product A3product6("6","A","A3","T2","now",0);
    Product A3product7("7","A","A3","T3","now",0);

    Product A4product1("1","A","A4","T1","now",0);
    Product A4product2("2","A","A4","T1","now",0);
    Product A4product3("3","A","A4","T1","now",0);
    Product A4product4("4","A","A4","T2","now",0);
    Product A4product5("5","A","A4","T2","now",0);
    Product A4product6("6","A","A4","T2","now",0);
    Product A4product7("7","A","A4","T3","now",0);
    QaddDataWhileRefreshBatch("admin",A1product1);
    QaddDataWhileRefreshBatch("admin",A1product2);
    QaddDataWhileRefreshBatch("admin",A1product3);
    QaddDataWhileRefreshBatch("admin",A1product4);
    QaddDataWhileRefreshBatch("admin",A1product5);
    QaddDataWhileRefreshBatch("admin",A1product6);
    QaddDataWhileRefreshBatch("admin",A1product7);

    QaddDataWhileRefreshBatch("admin",A2product1);
    QaddDataWhileRefreshBatch("admin",A2product2);
    QaddDataWhileRefreshBatch("admin",A2product3);
    QaddDataWhileRefreshBatch("admin",A2product4);
    QaddDataWhileRefreshBatch("admin",A2product5);
    QaddDataWhileRefreshBatch("admin",A2product6);
    QaddDataWhileRefreshBatch("admin",A2product7);

    QaddDataWhileRefreshBatch("admin",A3product1);
    QaddDataWhileRefreshBatch("admin",A3product2);
    QaddDataWhileRefreshBatch("admin",A3product3);
    QaddDataWhileRefreshBatch("admin",A3product4);
    QaddDataWhileRefreshBatch("admin",A3product5);
    QaddDataWhileRefreshBatch("admin",A3product6);
    QaddDataWhileRefreshBatch("admin",A3product7);

    QaddDataWhileRefreshBatch("admin",A4product1);
    QaddDataWhileRefreshBatch("admin",A4product2);
    QaddDataWhileRefreshBatch("admin",A4product3);
    QaddDataWhileRefreshBatch("admin",A4product4);
    QaddDataWhileRefreshBatch("admin",A4product5);
    QaddDataWhileRefreshBatch("admin",A4product6);
    QaddDataWhileRefreshBatch("admin",A4product7);

    QdeleteData("admin",A4product7);
}

Qres dbhelper::QexistOrInsert(Product product)
{
    QSqlQuery query;
    Qres _return;
    query.prepare("select * from Product where number= ? and batchid=? and tray=?");
    query.addBindValue(product.number);
    query.addBindValue(product.batchid);
    query.addBindValue(product.tray);
    if(query.exec())
    {
        if(query.next())
        {
            //no operation
            _return.error=0;
            _return.msg="exist so no insert";
            _return.success=1;
        }
        else
        {
            //insert
            _return = addData(product);
            qDebug()<<"add product:batchid:"+product.batchid+" number:"+product.number+" tray:"+product.tray;
        }
    }
    else
    {
        //database error
        _return.error=1;
        _return.msg="database error";
        _return.success=0;
    }
    return _return;
}

Qres dbhelper::Qrefreshfile()
{
    Qres _return;
    QFile file("Lo1.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    FileData temp;
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QString str(line);
        temp.data=temp.data+str;
        if(str!="")
        {
            QList<QString> list = str.split(',');
            Product product(list[0],list[1],list[2],list[3],list[4],list[5].toInt());
            QexistOrInsert(product);
        }
    }
    return _return;
}

QList<Qbatch> dbhelper::QgetBatch()
{
    QSqlQuery query;
    QList<Qbatch> list;
    query.prepare("select * from Batch");
    if(query.exec())
    {
        while(query.next())
        {
            QString batchid=query.value("batchid").toString();
            QString batchsum=query.value("batchsum").toString();
            QString batchamout=query.value("batchamout").toString();
            Qbatch batch;
            batch.batchamout=batchamout;
            batch.batchid=batchid;
            batch.batchsum=batchsum;
            list.append(batch);
        }
        return list;
    }
    else
    {
        return list;
    }
}

QList<Product> dbhelper::QgetDataorderby(int attr,int pattern)
{
//1:type 2:batchid 3:tray 4:time 5:flag      pattern: 1:increase 2: descrease
    QList<Product> list;
    QString Qattr;
    QString Qpattern;
    switch(attr)
    {
    case 1:Qattr="type";break;
    case 2:Qattr="batchid";break;
    case 3:Qattr="tray";break;
    case 4:Qattr="time";break;
    case 5:Qattr="flag";break;
    }
    if(pattern==1)
    {
        Qpattern="";
    }
    else
    {
       Qpattern="desc";
    }

    QSqlQuery query;
   if (query.exec("select * from product order by "+Qattr+" "+Qpattern))
   {
       while(query.next())
       {
           Product temp;
           temp.number=query.value("number").toString();
           temp.type=query.value("type").toString();
           temp.batchid=query.value("batchid").toString();
           temp.tray=query.value("tray").toString();
           temp.time=query.value("time").toString();
           temp.flag=query.value("flag").toInt();
           list.append(temp);
       }
   }
return list;


}
