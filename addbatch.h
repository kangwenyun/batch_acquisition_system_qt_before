#ifndef ADDBATCH_H
#define ADDBATCH_H

#include "dbhelper.h"
#include <QDialog>
#include <QString>

namespace Ui {
class addBatch;
}

class addBatch : public QDialog
{
    Q_OBJECT

public:
    explicit addBatch(QWidget *parent = 0);
    ~addBatch();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addBatch *ui;
    dbhelper helper;
    QString userId;
};

#endif // ADDBATCH_H
