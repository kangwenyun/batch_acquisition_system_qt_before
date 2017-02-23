#include "getlog.h"
#include "ui_getlog.h"

//工作日志获得
GetLog::GetLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetLog)
{
    ui->setupUi(this);
}

GetLog::~GetLog()
{
    delete ui;
}
