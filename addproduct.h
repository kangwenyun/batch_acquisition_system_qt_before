#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include "product.h"
#include "dbhelper.h"
#include "session.h"
#include <QWidget>
#include <QString>

//货物修改和增加的弹框
namespace Ui {
class addProduct;
}

class addProduct : public QWidget
{
    Q_OBJECT

public:
    explicit addProduct(QWidget *parent = 0);
    void setProduct(Product curproduct);
    ~addProduct();

signals:
    void save();

private slots:
    void on_save_button_clicked();

private:
    Ui::addProduct *ui;
    Product curproduct;
    bool change;//1表示change,0表示add
    dbhelper helper;
    QString userId;
};

#endif // ADDPRODUCT_H
