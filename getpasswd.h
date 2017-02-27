#ifndef GETPASSWD_H
#define GETPASSWD_H

#include <QWidget>

class Login;

namespace Ui {
class GetPasswd;
}

class GetPasswd : public QWidget
{
    Q_OBJECT

public:
    explicit GetPasswd(QWidget *parent = 0);
    ~GetPasswd();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GetPasswd *ui;
    Login *lg;
};

#endif // GETPASSWD_H
