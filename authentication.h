#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QWidget>

namespace Ui {
class Authentication;
}

class Authentication : public QWidget
{
    Q_OBJECT

public:
    explicit Authentication(QWidget *parent = 0);
    ~Authentication();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Authentication *ui;
};

#endif // AUTHENTICATION_H
