#ifndef VIEWBATCH_H
#define VIEWBATCH_H

#include <QWidget>

namespace Ui {
class ViewBatch;
}

class ViewBatch : public QWidget
{
    Q_OBJECT

public:
    explicit ViewBatch(QWidget *parent = 0);
    ~ViewBatch();

private:
    Ui::ViewBatch *ui;
};

#endif // VIEWBATCH_H
