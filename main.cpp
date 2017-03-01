#include "login.h"
#include "mainwindow.h"
#include <QApplication>
#include<viewbatch.h>
#include<viewdata.h>
#include<refreshdata.h>
#include<test.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.show();
    return a.exec();
}
