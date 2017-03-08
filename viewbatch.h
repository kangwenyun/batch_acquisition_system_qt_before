#ifndef VIEWBATCH_H
#define VIEWBATCH_H

#include "qbatch.h"
#include "dbhelper.h"
#include <QWidget>
#include <QList>
namespace Ui {
class ViewBatch;
}

class ViewBatch : public QWidget
{
    Q_OBJECT

public:
    explicit ViewBatch(QWidget *parent = 0);
    ~ViewBatch();

private slots:
    void on_batchInfo_doubleClicked(const QModelIndex &index);

    void on_add_batch_clicked();

    void on_batchInfo_clicked(const QModelIndex &index);

    void on_refresh_batch_clicked();

private:
    Ui::ViewBatch *ui;
    dbhelper helper;
    QList<Qbatch> batchList;
};

#endif // VIEWBATCH_H
