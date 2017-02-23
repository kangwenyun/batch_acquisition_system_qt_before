#include "correctlog.h"
#include "ui_correctlog.h"

//特权用户可更改相应错误
CorrectLog::CorrectLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrectLog)
{
    ui->setupUi(this);
}

CorrectLog::~CorrectLog()
{
    delete ui;
}
