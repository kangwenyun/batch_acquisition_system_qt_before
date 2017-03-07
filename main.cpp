#include "login.h"
#include "mainwindow.h"
#include <QApplication>
#include <dbhelper.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dbhelper db;

   // db.deleteall();
    //db.initdb();
    Login l;
    l.show();
    return a.exec();
}
