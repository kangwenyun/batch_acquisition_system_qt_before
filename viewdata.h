#ifndef VIEWDATA_H
#define VIEWDATA_H

#include "dbhelper.h"
#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class ViewData;
}

class ViewData : public QWidget
{
    Q_OBJECT

public:
    explicit ViewData(QWidget *parent = 0);
    ~ViewData();
    void setWriteability(QList<QTableWidgetItem *> items , bool bl);

private slots:
    void on_data_change_clicked();

    void on_data_save_clicked();

    void on_data_refresh_clicked();

    void on_data_delete_clicked();

    void on_data_add_clicked();

private:
    Ui::ViewData *ui;
    dbhelper helper;

};

#endif // VIEWDATA_H
