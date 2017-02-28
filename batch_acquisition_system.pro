#-------------------------------------------------
#
# Project created by QtCreator 2017-02-09T16:09:42
#
#-------------------------------------------------

QT       += core gui widgets
QT +=  sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = batch_acquisition_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    login.cpp \
    registered.cpp \
    getpasswd.cpp \
    mainwindow.cpp \
    changepasswd.cpp \
    authentication.cpp \
    registrationinfo.cpp \
    getlog.cpp \
    detaillog.cpp \
    correctlog.cpp \
    viewbatch.cpp \
    modifybatch.cpp \
    submitbatch.cpp \
    viewdata.cpp \
    maintaindata.cpp \
    uploaddata.cpp \
    refreshdata.cpp \
    setpermissions.cpp \
    viewproline.cpp \
    setproline.cpp \
    modifyproline.cpp \
    currentperson.cpp \
    serverservice.cpp \
    dbhelper.cpp \
    qres.cpp \
    quser.cpp

HEADERS  += \
    login.h \
    registered.h \
    getpasswd.h \
    mainwindow.h \
    changepasswd.h \
    authentication.h \
    registrationinfo.h \
    getlog.h \
    detaillog.h \
    correctlog.h \
    viewbatch.h \
    modifybatch.h \
    submitbatch.h \
    viewdata.h \
    maintaindata.h \
    uploaddata.h \
    refreshdata.h \
    setpermissions.h \
    viewproline.h \
    setproline.h \
    modifyproline.h \
    session.h \
    serverservice.h \
    dbhelper.h \
    qres.h \
    quser.h

FORMS    += \
    login.ui \
    registered.ui \
    getpasswd.ui \
    mainwindow.ui \
    changepasswd.ui \
    authentication.ui \
    registrationinfo.ui \
    getlog.ui \
    detaillog.ui \
    correctlog.ui \
    viewbatch.ui \
    modifybatch.ui \
    submitbatch.ui \
    viewdata.ui \
    maintaindata.ui \
    uploaddata.ui \
    refreshdata.ui \
    setpermissions.ui \
    viewproline.ui \
    setproline.ui \
    modifyproline.ui


