#ifndef CHANGEPASSWD_H
#define CHANGEPASSWD_H

#include <QWidget>

namespace Ui {
class ChangePasswd;
}

class ChangePasswd : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswd(QWidget *parent = 0);
    ~ChangePasswd();

private:
    Ui::ChangePasswd *ui;
};

#endif // CHANGEPASSWD_H
