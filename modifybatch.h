#ifndef MODIFYBATCH_H
#define MODIFYBATCH_H

#include <QWidget>

namespace Ui {
class ModifyBatch;
}

class ModifyBatch : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyBatch(QWidget *parent = 0);
    ~ModifyBatch();

private:
    Ui::ModifyBatch *ui;
};

#endif // MODIFYBATCH_H
