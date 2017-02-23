#include "uploaddata.h"
#include "ui_uploaddata.h"

//数据的上传
UploadData::UploadData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UploadData)
{
    ui->setupUi(this);
}

UploadData::~UploadData()
{
    delete ui;
}
