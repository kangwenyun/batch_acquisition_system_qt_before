#ifndef MAINTAINDATA_H
#define MAINTAINDATA_H

#include "dbhelper.h"
#include "product.h"
#include "saveproduct.h"
#include <QWidget>
#include <QString>

namespace Ui {
class MaintainData;
}

class MaintainData : public QWidget
{
    Q_OBJECT

public:
    explicit MaintainData(QWidget *parent = 0);
    ~MaintainData();
    void setWriteability(int row , bool bl);

private slots:
    void on_data_change_clicked();

    void on_data_refresh_clicked();

    void on_data_delete_clicked();

    void on_data_add_clicked();

private:
    Ui::MaintainData *ui;
    dbhelper helper;
    QString userId;
    Product curproduct;
    int row;//当前选中行
    saveProduct *sp;
};

#endif // MAINTAINDATA_H
