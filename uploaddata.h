#ifndef UPLOADDATA_H
#define UPLOADDATA_H

#include <QWidget>

namespace Ui {
class UploadData;
}

class UploadData : public QWidget
{
    Q_OBJECT

public:
    explicit UploadData(QWidget *parent = 0);
    ~UploadData();

private:
    Ui::UploadData *ui;
};

#endif // UPLOADDATA_H
