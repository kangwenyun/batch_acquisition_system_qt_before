#ifndef QTRAY_H
#define QTRAY_H
#include<QString>
#include<QList>
#include<product.h>
class Qtray
{
public:
    Qtray();
    QString tray;
    QList<Product> productlist;
};

#endif // QTRAY_H
