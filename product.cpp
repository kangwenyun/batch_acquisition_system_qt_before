#include "product.h"

Product::Product()
{

}
Product::Product(QString m_number, QString m_type, QString m_batchid, QString m_tray, QString m_time, int m_flag)
{
    number=m_number;
    type=m_type;
    batchid=m_batchid;
    tray=m_tray;
    time=m_time;
    flag=m_flag;
}
