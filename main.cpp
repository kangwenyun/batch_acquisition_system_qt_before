#include "login.h"
#include "mainwindow.h"
#include <QApplication>
#include <dbhelper.h>
#include<test.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dbhelper db;

//    db.deleteall();
    //db.initdb();
    test l;
    l.show();
    return a.exec();
}
