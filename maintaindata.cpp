#include "maintaindata.h"
#include "ui_maintaindata.h"

//数据的维护
MaintainData::MaintainData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaintainData)
{
    ui->setupUi(this);
}

MaintainData::~MaintainData()
{
    delete ui;
}
