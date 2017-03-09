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

private slots:
    void on_data_change_clicked();

    void on_data_refresh_clicked();

    void on_data_delete_clicked();

    void on_data_add_clicked();

    void on_data_deleteAll_clicked();

private:
    Ui::MaintainData *ui;
    dbhelper helper;
    QString userId;//当前用户id
    Product curproduct;//当前选中货物的具体信息
    int row;//当前选中行
    saveProduct *sp;//修改增加货物时的弹框
};

#endif // MAINTAINDATA_H
