#ifndef VIEWDATA_H
#define VIEWDATA_H

#include "dbhelper.h"
#include "product.h"
#include "saveproduct.h"
#include <QWidget>
#include <QString>

namespace Ui {
class ViewData;
}

class ViewData : public QWidget
{
    Q_OBJECT

public:
    explicit ViewData(QWidget *parent = 0);
    ~ViewData();
    void setWriteability(int row , bool bl);

private slots:
    void on_data_change_clicked();

    void on_data_refresh_clicked();

    void on_data_delete_clicked();

    void on_data_add_clicked();

private:
    Ui::ViewData *ui;
    dbhelper helper;
    QString userId;
    Product curproduct;
    int row;//当前选中行
    saveProduct *sp;
};

#endif // VIEWDATA_H
