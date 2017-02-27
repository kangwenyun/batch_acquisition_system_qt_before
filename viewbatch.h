#ifndef VIEWBATCH_H
#define VIEWBATCH_H

#include <QWidget>
#include<QTableWidget>
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

private:
    Ui::ViewBatch *ui;
    QTableWidget* batchInfo;
};

#endif // VIEWBATCH_H
