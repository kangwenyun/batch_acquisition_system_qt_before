#include "login.h"
#include "mainwindow.h"
#include <QApplication>
#include<viewbatch.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
//    MainWindow l;
    l.show();

    return a.exec();
}
