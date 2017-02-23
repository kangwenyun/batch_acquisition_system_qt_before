#include "modifybatch.h"
#include "ui_modifybatch.h"

//批次错误信息的修改
ModifyBatch::ModifyBatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyBatch)
{
    ui->setupUi(this);
}

ModifyBatch::~ModifyBatch()
{
    delete ui;
}
