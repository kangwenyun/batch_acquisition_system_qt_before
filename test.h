#ifndef TEST_H
#define TEST_H

#include <QDialog>

namespace Ui {
class Test;
}

class Test : public QDialog
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = 0);
    ~Test();

private slots:
    void on_adddata_clicked();
    void on_pushButton_clicked();

private:
    Ui::Test *ui;
};

#endif // TEST_H
