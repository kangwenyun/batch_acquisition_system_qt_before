#ifndef CORRECTLOG_H
#define CORRECTLOG_H

#include <QWidget>

namespace Ui {
class CorrectLog;
}

class CorrectLog : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectLog(QWidget *parent = 0);
    ~CorrectLog();

private:
    Ui::CorrectLog *ui;
};

#endif // CORRECTLOG_H
