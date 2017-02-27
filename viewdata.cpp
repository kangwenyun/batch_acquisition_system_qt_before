#include "viewdata.h"
#include "ui_viewdata.h"

//数据的查看
ViewData::ViewData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewData)
{
    ui->setupUi(this);
    // 自适应列宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ViewData::~ViewData()
{
    delete ui;
}
