#ifndef CHANGEPASSWD_H
#define CHANGEPASSWD_H

#include <QWidget>
#include <QString>

namespace Ui {
class ChangePasswd;
}

class ChangePasswd : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswd(QWidget *parent = 0);
    ~ChangePasswd();

private slots:

    void on_ok_button_clicked();

private:
    Ui::ChangePasswd *ui;
    QString userId;
};

#endif // CHANGEPASSWD_H
