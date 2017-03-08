#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "authentication.h"
#include "registrationinfo.h"
#include "changepasswd.h"
#include "getlog.h"
#include "detaillog.h"
#include "correctlog.h"
#include "viewbatch.h"
#include "submitbatch.h"
#include "maintaindata.h"
#include "viewdata.h"
#include "uploaddata.h"
#include "refreshdata.h"
#include "setpermissions.h"
#include "viewproline.h"
#include "setproline.h"
#include "modifyproline.h"
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QMenuBar>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();
    Authentication *atc = new Authentication;
    setCentralWidget(atc);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    //系统登录，身份认证
    authentication = new QAction(tr("身份认证"),this);
    authentication->setStatusTip(tr("身份认证"));
    connect(authentication,SIGNAL(hovered()),this,SLOT(authentication_clicked()));

    //员工注册信息的查看
    registrationInfo = new QAction(tr("注册信息查看"),this);
    registrationInfo->setStatusTip(tr("注册信息查看"));
    connect(registrationInfo,SIGNAL(triggered()),this,SLOT(registrationInfo_clicked()));

    //密码的设置修改
    changePasswd = new QAction(tr("密码修改"),this);
    changePasswd->setStatusTip(tr("密码修改"));
    connect(changePasswd,SIGNAL(triggered()),this,SLOT(changePasswd_clicked()));

    //工作日志获得
    getLog = new QAction(tr("日志获得"),this);
    getLog->setStatusTip(tr("日志获得"));
    connect(getLog,SIGNAL(triggered()),this,SLOT(getLog_clicked()));

    //工作详情查看
    detailLog = new QAction(tr("详情查看"),this);
    detailLog->setStatusTip(tr("详情查看"));
    connect(detailLog,SIGNAL(triggered()),this,SLOT(detailLog_clicked()));

    //特权用户可更改相应错误
    correctLog = new QAction(tr("批次错误更改"),this);
    correctLog->setStatusTip(tr("批次错误更改"));
    connect(correctLog,SIGNAL(triggered()),this,SLOT(correctLog_clicked()));

    //所有批次的信息的查看
    viewBatch = new QAction(tr("批次信息查看"),this);
    viewBatch->setStatusTip(tr("批次信息查看"));
    connect(viewBatch,SIGNAL(triggered()),this,SLOT(viewBatch_clicked()));

    //来自WMS的批次请求的提交
    submitBatch = new QAction(tr("请求提交"),this);
    submitBatch->setStatusTip(tr("请求提交"));
    connect(submitBatch,SIGNAL(triggered()),this,SLOT(submitBatch_clicked()));

    //数据的查看
    viewData = new QAction(tr("数据查看"),this);
    viewData->setStatusTip(tr("数据查看"));
    connect(viewData,SIGNAL(triggered()),this,SLOT(viewData_clicked()));

    //数据的维护
    maintainData = new QAction(tr("数据维护"),this);
    maintainData->setStatusTip(tr("数据维护"));
    connect(maintainData,SIGNAL(triggered()),this,SLOT(maintainData_clicked()));

    //数据的上传
    uploadData = new QAction(tr("数据上传"),this);
    uploadData->setStatusTip(tr("数据上传"));
    connect(uploadData,SIGNAL(triggered()),this,SLOT(uploadData_clicked()));

    //数据实时刷新
    refreshData = new QAction(tr("数据实时刷新"),this);
    refreshData->setStatusTip(tr("数据实时刷新"));
    connect(refreshData,SIGNAL(triggered()),this,SLOT(refreshData_clicked()));

    //对不同的用户设置不同的权限
    setPermissions = new QAction(tr("权限设置"),this);
    setPermissions->setStatusTip(tr("权限设置"));
    connect(setPermissions,SIGNAL(triggered()),this,SLOT(setPermissions_clicked()));

    //生产线信息的查看
    viewProLine = new QAction(tr("生产线信息查看"),this);
    viewProLine->setStatusTip(tr("生产线信息查看"));
    connect(viewProLine,SIGNAL(triggered()),this,SLOT(viewProLine_clicked()));

    //生产线信息的设置
    setProLine = new QAction(tr("生产线信息设置"),this);
    setProLine->setStatusTip(tr("生产线信息设置"));
    connect(setProLine,SIGNAL(triggered()),this,SLOT(setProLine_clicked()));

    //生产线信息的修改
    modifyProLine = new QAction(tr("生产线信息修改"),this);
    modifyProLine->setStatusTip(tr("生产线信息修改"));
    connect(modifyProLine,SIGNAL(triggered()),this,SLOT(modifyProLine_clicked()));
}

void MainWindow::createMenus()
{
    //个人信息管理
    person_info = ui->person_info;
    QList<QAction*> pi;
    pi << authentication << registrationInfo << changePasswd ;
    person_info->addActions(pi);

    //日志管理
    log = ui->log;
    QList<QAction*> lg;
    lg << getLog << detailLog << correctLog ;
    log->addActions(lg);

    //批次信息管理
    batch_info = ui->batch_info;
    QList<QAction*> bi;
    bi << viewBatch << submitBatch ;
    batch_info->addActions(bi);

    //权限管理
    authority = ui->authority;
    QList<QAction*> auth;
    auth <<  setPermissions ;
    authority->addActions(auth);

    //生产线信息管理
    proLine_info = ui->proLine_info;
    QList<QAction*> pli;
     pli << viewProLine << setProLine << modifyProLine ;
    proLine_info->addActions(pli);

    //数据管理
    data = ui->data;
    QList<QAction*> dt;

    dt<<viewData << maintainData << uploadData ;
    data->addActions(dt);
}

//系统登录，身份认证
void MainWindow::authentication_clicked()
{
    Authentication *atc = new Authentication;
    setCentralWidget(atc);
}

//员工注册信息的查看
void MainWindow::registrationInfo_clicked()
{
    RegistrationInfo *ri = new RegistrationInfo;
    setCentralWidget(ri);
}

//密码的设置修改
void MainWindow::changePasswd_clicked()
{
    ChangePasswd *cp = new ChangePasswd;
    setCentralWidget(cp);
}

//工作日志获得
void MainWindow::getLog_clicked()
{
    GetLog *gl = new GetLog;
    setCentralWidget(gl);
}

//工作详情查看
void MainWindow::detailLog_clicked()
{
    DetailLog *dl = new DetailLog;
    setCentralWidget(dl);
}

//特权用户可更改相应错误
void MainWindow::correctLog_clicked()
{
    CorrectLog *cl = new CorrectLog;
    setCentralWidget(cl);
}

//所有批次的信息的查看
void MainWindow::viewBatch_clicked()
{
    ViewBatch *vb = new ViewBatch;
    setCentralWidget(vb);
}

//来自WMS的批次请求的提交
void MainWindow::submitBatch_clicked()
{
    SubmitBatch *sb = new SubmitBatch;
    setCentralWidget(sb);
}

//数据的查看
void MainWindow::viewData_clicked()
{
    ViewData *vd = new ViewData;
    setCentralWidget(vd);
}

//数据的维护
void MainWindow::maintainData_clicked()
{
    MaintainData *md = new MaintainData;
    setCentralWidget(md);
}

//数据的上传
void MainWindow::uploadData_clicked()
{
    UploadData *ud = new UploadData;
    setCentralWidget(ud);
}

//数据实时刷新
void MainWindow::refreshData_clicked()
{
    RefreshData *rd = new RefreshData;
    setCentralWidget(rd);
}

//对不同的用户设置不同的权限
void MainWindow::setPermissions_clicked()
{
    SetPermissions *sp = new SetPermissions;
    setCentralWidget(sp);
}

//生产线信息的查看
void MainWindow::viewProLine_clicked()
{
    ViewProLine *vpl = new ViewProLine;
    setCentralWidget(vpl);
}

//生产线信息的设置
void MainWindow::setProLine_clicked()
{
    SetProLine *spl = new SetProLine;
    setCentralWidget(spl);
}

//生产线信息的修改
void MainWindow::modifyProLine_clicked()
{
    ModifyProLine *mpl = new ModifyProLine;
    setCentralWidget(mpl);
}
