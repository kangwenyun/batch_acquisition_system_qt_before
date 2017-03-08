#ifndef VIEWDATA_H
#define VIEWDATA_H

#include "dbhelper.h"
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

private slots:
    void on_data_refresh_clicked();

private:
    Ui::ViewData *ui;
    QString userId;
    dbhelper helper;
};

#endif // VIEWDATA_H
