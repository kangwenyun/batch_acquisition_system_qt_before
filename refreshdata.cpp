#include "refreshdata.h"
#include "ui_refreshdata.h"

//数据实时刷新
RefreshData::RefreshData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RefreshData)
{
    ui->setupUi(this);
}

RefreshData::~RefreshData()
{
    delete ui;
}
