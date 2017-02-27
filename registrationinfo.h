#ifndef REGISTRATIONINFO_H
#define REGISTRATIONINFO_H

#include <QWidget>

namespace Ui {
class RegistrationInfo;
}

class RegistrationInfo : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationInfo(QWidget *parent = 0);
    ~RegistrationInfo();

private slots:
    void on_edit_ok_button_clicked();

private:
    Ui::RegistrationInfo *ui;
    QString userId;
    void setWriteability(bool bl);
};

#endif // REGISTRATIONINFO_H
