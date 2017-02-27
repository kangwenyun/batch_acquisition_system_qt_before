#ifndef DETAILLOG_H
#define DETAILLOG_H

#include <QWidget>

namespace Ui {
class DetailLog;
}

class DetailLog : public QWidget
{
    Q_OBJECT

public:
    explicit DetailLog(QWidget *parent = 0);
    ~DetailLog();

private:
    Ui::DetailLog *ui;
};

#endif // DETAILLOG_H
