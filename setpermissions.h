#ifndef SETPERMISSIONS_H
#define SETPERMISSIONS_H

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

private:
    Ui::SetPermissions *ui;
};

#endif // SETPERMISSIONS_H
