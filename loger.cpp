#include "loger.h"
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
#include <QDir>
//QLoggingCategory  m_category("Batch");
Loger* Loger::getInstance()
{
    static Loger* logger=new Loger();
    //QLoggingCategory::setFilterRules(QStringLiteral("Batch.debug=true"));
    //qSetMessagePattern("%{category}  %{message}");
    return logger;
}
void Loger::setLoger(QString user, QString operation)
{
    QDateTime time = QDateTime::currentDateTime();
    QString logitem=time.toString("yyyy-MM-dd hh:mm:ss")+"^"+user+"^"+operation;
    QString filename=time.toString("yyyy-MM-dd")+".txt";
    qDebug()<<logitem;
    QFile file("Log/"+filename);
    QDir *temp = new QDir;
    bool exist = temp->exists("Log");
    if(!exist)
    {
        temp->mkdir("Log");
    }
    if(file.exists())
    {
        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            qDebug()<<"error";
            return;
        }
        QTextStream out(&file);
        out <<logitem<<endl;
        file.close();
    }
    else
    {
        qDebug()<<"create file success";
        file.open( QIODevice::Append );
        QTextStream out(&file);
        out <<logitem<<endl;
        file.close();
    }
}

Loger::Loger(){}
