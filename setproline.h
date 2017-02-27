#ifndef SETPROLINE_H
#define SETPROLINE_H

#include <QWidget>

namespace Ui {
class SetProLine;
}

class SetProLine : public QWidget
{
    Q_OBJECT

public:
    explicit SetProLine(QWidget *parent = 0);
    ~SetProLine();

private:
    Ui::SetProLine *ui;
};

#endif // SETPROLINE_H
