#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>

class Registered;
class GetPasswd;
class MainWindow;

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void setUserId(QString id);

private slots:
    void on_login_clicked();
    void on_get_passwd_clicked();
    void on_registered_clicked();

private:
    Ui::Login *ui;
    //用户名字符串
    QString userId;
    //不能用明文保存密码，存储密码hash值
    QByteArray passwdHash;
    //注册界面
    Registered *registered;
    //找回密码
    GetPasswd *getPasswd;
    //主界面
    MainWindow *mainWindow;
};

#endif // WIDGET_H
