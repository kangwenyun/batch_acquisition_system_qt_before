#include "addproduct.h"
#include "ui_addproduct.h"

addProduct::addProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addProduct)
{
    ui->setupUi(this);
    // 自适应列宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowCount(1);
}

addProduct::~addProduct()
{
    delete ui;
}
