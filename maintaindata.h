#ifndef MAINTAINDATA_H
#define MAINTAINDATA_H

#include <QWidget>

namespace Ui {
class MaintainData;
}

class MaintainData : public QWidget
{
    Q_OBJECT

public:
    explicit MaintainData(QWidget *parent = 0);
    ~MaintainData();

private:
    Ui::MaintainData *ui;
};

#endif // MAINTAINDATA_H
