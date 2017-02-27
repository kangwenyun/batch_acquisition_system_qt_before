#ifndef MODIFYPROLINE_H
#define MODIFYPROLINE_H

#include <QWidget>

namespace Ui {
class ModifyProLine;
}

class ModifyProLine : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyProLine(QWidget *parent = 0);
    ~ModifyProLine();

private:
    Ui::ModifyProLine *ui;
};

#endif // MODIFYPROLINE_H
