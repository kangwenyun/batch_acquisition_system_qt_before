#ifndef REFRESHDATA_H
#define REFRESHDATA_H

#include <QWidget>

namespace Ui {
class RefreshData;
}

class RefreshData : public QWidget
{
    Q_OBJECT

public:
    explicit RefreshData(QWidget *parent = 0);
    ~RefreshData();

private:
    Ui::RefreshData *ui;
};

#endif // REFRESHDATA_H
