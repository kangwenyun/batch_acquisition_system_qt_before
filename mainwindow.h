#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();
    void createMenus();

public slots:
    void authentication_clicked();
    void registrationInfo_clicked();
    void changePasswd_clicked();
    void getLog_clicked();
    void detailLog_clicked();
    void correctLog_clicked();
    void viewBatch_clicked();
    void submitBatch_clicked();
    void viewData_clicked();
    void maintainData_clicked();
    void uploadData_clicked();
    void refreshData_clicked();
    void setPermissions_clicked();
    void viewProLine_clicked();
    void setProLine_clicked();
    void modifyProLine_clicked();

private:
    Ui::MainWindow *ui;

    QMenu *person_info;
    QMenu *log;
    QMenu *batch_info;
    QMenu *authority;
    QMenu *proLine_info;
    QMenu *data;

    QAction *authentication;
    QAction *registrationInfo;
    QAction *changePasswd;

    QAction *getLog;
    QAction *detailLog;
    QAction *correctLog;

    QAction *viewBatch;
    QAction *submitBatch;

    QAction *viewData;
    QAction *maintainData;
    QAction *uploadData;
    QAction *refreshData;

    QAction *setPermissions;

    QAction *viewProLine;
    QAction *setProLine;
    QAction *modifyProLine;
};

#endif // MAINWINDOW_H
