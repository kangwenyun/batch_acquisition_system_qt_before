#include "submitbatch.h"
#include "ui_submitbatch.h"

//来自WMS的批次请求的提交
SubmitBatch::SubmitBatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubmitBatch)
{
    ui->setupUi(this);
}

SubmitBatch::~SubmitBatch()
{
    delete ui;
}
