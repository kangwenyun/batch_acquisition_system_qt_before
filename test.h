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
<<<<<<< HEAD
    void on_adddata_clicked();
=======
    void on_pushButton_clicked();
>>>>>>> 0d5c39fb7e33477d9b670eefe5e3e85335349951

private:
    Ui::Test *ui;
};

#endif // TEST_H
