#ifndef REGISTERED_H
#define REGISTERED_H

#include "login.h"
#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class Registered;
}

class Registered : public QWidget
{
    Q_OBJECT

public:
    explicit Registered(QWidget *parent = 0);
    ~Registered();

private slots:
    void on_ok_button_clicked();

private:
    Ui::Registered *ui;
    //性别单选按钮分组
    QButtonGroup *genderGroup;
    //注册界面
    Login *lg;
};

#endif // REGISTERED_H
