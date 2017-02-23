#include "detaillog.h"
#include "ui_detaillog.h"

//工作详情查看
DetailLog::DetailLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailLog)
{
    ui->setupUi(this);
}

DetailLog::~DetailLog()
{
    delete ui;
}
