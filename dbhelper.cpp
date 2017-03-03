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
        _return.msg="change userinformation successfully";
        _return.success=1;
        return _return;
    }
    else
    {
        _return.error=1;
        _return.msg="database happened error";
        _return.success=0;
        return _return;
    }
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
        if(uquery.value("level").toString()=="0")
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
        if(uquery.value("level").toString()=="0")
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
            if(query.value(0).toString()=="0")
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
            _return.msg="getuserinformation success";
            _return.success=1;

        }
        else
        {

            _return.error=0;
            _return.msg="getinfomation failed";
            _return.success=0;
        }
    }
    else
    {

        _return.error=1;
        _return.msg="datebase happened error";
        _return.success=0;
    }
    return _return;
}

Qres dbhelper::QaddBatch(QString batchid,QString batchsum)
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
            _return.msg="batchid has existed!";
            _return.success=0;
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
                _return.msg="success add batch!";
                _return.success=1;
            }
            else
            {
                _return.error=1;
                _return.msg="datebase error2";
                _return.success=0;
            }
        }
    }
    else
    {
        _return.error=1;
        _return.msg="datebase error1";
        _return.success=0;
    }
    return _return;


}

Qres dbhelper::QaddDataWhileRefreshBatch(Product product)
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
            add=addDate(product);
            if(add.success==1)
            {
                refresh=RefreshBatch(batchid);
                if(refresh.success==1)
                {
                    _return.error=0;
                    _return.msg="QaddDataWhileRefreshBatch success";
                    _return.success=1;
                }
                else
                {
                    _return.error=refresh.error;
                    _return.msg=refresh.msg;
                    _return.success=refresh.success;
                }
            }
            else
            {
                _return.error=add.error;
                _return.msg=add.msg;
                _return.success=add.success;
            }
        }
        else
        {
            product.flag=1;
            addDate(product);
            _return.error=0;
            _return.msg="not exist batchid  flag=1";
            _return.success=1;
        }
    }
    else
    {
        //database error
        _return.error=1;
        _return.msg="database error 610";
        _return.success=0;
    }
    return _return;
}

Qres dbhelper::addDate(Product product)
{
    Qres _return;
    QSqlQuery query;
    query.prepare("insert into product (number,type,batchid,tray,time,flag)  values ( :number,:type,:batchid,:tray,:time,:flag)");
    query.bindValue(":number",product.number);
    query.bindValue(":type",product.type);
    query.bindValue(":batchid",product.batchid);
    query.bindValue(":tray",product.tray);
    query.bindValue(":time",product.time);
    query.bindValue(":flag",product.flag);
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
        _return.msg="database error 611";
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
                _return.msg="update batch success";
                _return.success=1;
            }
            else
            {
                //data base error
                _return.error=1;
                _return.msg="database error 642";
                _return.success=0;
            }
        }
        else
        {
            //not exist batchid
            qDebug()<<"3";
            _return.error=0;
            _return.msg="not exist batchid";
            _return.success=0;
        }
    }
    else
    {
        //database error
        qDebug()<<"4";
        _return.error=1;
        _return.msg="database error 658";
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
                _return.msg="database error 737";
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
        _return.msg="database error 750";
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
    QaddBatch("A1","50");
    QaddBatch("A2","60");
    QaddBatch("A3","40");
    QaddBatch("A4","30");
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
    QaddDataWhileRefreshBatch(A1product1);
    QaddDataWhileRefreshBatch(A1product2);
    QaddDataWhileRefreshBatch(A1product3);
    QaddDataWhileRefreshBatch(A1product4);
    QaddDataWhileRefreshBatch(A1product5);
    QaddDataWhileRefreshBatch(A1product6);
    QaddDataWhileRefreshBatch(A1product7);

    QaddDataWhileRefreshBatch(A2product1);
    QaddDataWhileRefreshBatch(A2product2);
    QaddDataWhileRefreshBatch(A2product3);
    QaddDataWhileRefreshBatch(A2product4);
    QaddDataWhileRefreshBatch(A2product5);
    QaddDataWhileRefreshBatch(A2product6);
    QaddDataWhileRefreshBatch(A2product7);

    QaddDataWhileRefreshBatch(A3product1);
    QaddDataWhileRefreshBatch(A3product2);
    QaddDataWhileRefreshBatch(A3product3);
    QaddDataWhileRefreshBatch(A3product4);
    QaddDataWhileRefreshBatch(A3product5);
    QaddDataWhileRefreshBatch(A3product6);
    QaddDataWhileRefreshBatch(A3product7);

    QaddDataWhileRefreshBatch(A4product1);
    QaddDataWhileRefreshBatch(A4product2);
    QaddDataWhileRefreshBatch(A4product3);
    QaddDataWhileRefreshBatch(A4product4);
    QaddDataWhileRefreshBatch(A4product5);
    QaddDataWhileRefreshBatch(A4product6);
    QaddDataWhileRefreshBatch(A4product7);


}
