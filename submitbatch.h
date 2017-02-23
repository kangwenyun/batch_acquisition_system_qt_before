#ifndef SUBMITBATCH_H
#define SUBMITBATCH_H

#include <QWidget>

namespace Ui {
class SubmitBatch;
}

class SubmitBatch : public QWidget
{
    Q_OBJECT

public:
    explicit SubmitBatch(QWidget *parent = 0);
    ~SubmitBatch();

private:
    Ui::SubmitBatch *ui;
};

#endif // SUBMITBATCH_H
