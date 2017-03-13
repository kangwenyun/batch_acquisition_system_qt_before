#ifndef SETPERMISSIONS_H
#define SETPERMISSIONS_H

#include <QString>
#include <QWidget>

namespace Ui {
class SetPermissions;
}

class SetPermissions : public QWidget
{
    Q_OBJECT

public:
    explicit SetPermissions(QWidget *parent = 0);
    ~SetPermissions();

private slots:
    void on_change_button_clicked();

private:
    Ui::SetPermissions *ui;
    QString userId;
};

#endif // SETPERMISSIONS_H
