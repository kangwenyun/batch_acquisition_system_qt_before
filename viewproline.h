#ifndef VIEWPROLINE_H
#define VIEWPROLINE_H

#include <QWidget>

namespace Ui {
class ViewProLine;
}

class ViewProLine : public QWidget
{
    Q_OBJECT

public:
    explicit ViewProLine(QWidget *parent = 0);
    ~ViewProLine();

private:
    Ui::ViewProLine *ui;
};

#endif // VIEWPROLINE_H
