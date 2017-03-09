#ifndef PRODUCT_H
#define PRODUCT_H
#include<QString>
class Product
{
public:
    Product();
    Product(QString m_number,QString m_type,QString m_batchid,QString m_tray,QString m_time,int m_flag);
    int id;
    QString number;
    QString type;
    QString batchid;
    QString tray;
    QString time;
    int flag;
};

#endif // PRODUCT_H
