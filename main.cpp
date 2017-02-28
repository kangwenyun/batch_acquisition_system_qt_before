#include "login.h"
#include "mainwindow.h"
#include <QApplication>
#include<viewbatch.h>
#include<viewdata.h>
#include<refreshdata.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD
    Login l;
//    MainWindow l;
=======

    MainWindow l;

>>>>>>> 6623a40dada597d2f8bd877c8203bf8f8bbabef4
    l.show();

    return a.exec();
}
