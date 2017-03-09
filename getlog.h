#ifndef GETLOG_H
#define GETLOG_H

#include <QWidget>
#include <QString>

namespace Ui {
class GetLog;
}

class GetLog : public QWidget
{
    Q_OBJECT

public:
    explicit GetLog(QWidget *parent = 0);
    ~GetLog();
    void getData(QString fileTime);

private slots:
    void on_dateEdit_dateChanged(const QDate &date);

private:
    Ui::GetLog *ui;
};

#endif // GETLOG_H
