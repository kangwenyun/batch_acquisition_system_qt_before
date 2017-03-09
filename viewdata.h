#ifndef VIEWDATA_H
#define VIEWDATA_H
#include "filedata.h"
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
    void refresh();

private:
    Ui::ViewData *ui;
    QString userId;
    dbhelper helper;
    FileData all;
};

#endif // VIEWDATA_H
