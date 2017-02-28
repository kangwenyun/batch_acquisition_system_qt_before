#ifndef VIEWDATA_H
#define VIEWDATA_H

#include <QWidget>

namespace Ui {
class ViewData;
}

class ViewData : public QWidget
{
    Q_OBJECT

public:
    explicit ViewData(QWidget *parent = 0);
    ~ViewData();

private slots:
    void on_data_change_clicked();

    void on_data_save_clicked();

private:
    Ui::ViewData *ui;

};

#endif // VIEWDATA_H
