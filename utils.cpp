#include "utils.h"
#include "session.h"
#include <QString>
#include <QFile>
#include <QMessageBox>

Utils::Utils()
{

}

bool Utils::verifyPasswd(QFile& fileIn,QString& userId,QString passwd)
{
    //读取本地文件
    //读数据，读到匹配的就跳出
    bool success = false;
    while(!fileIn.atEnd())
    {
        QString accLine = fileIn.readLine();
        accLine=accLine.trimmed();//去除两边空格
        QList<QString> list = accLine.split(',');
        if(list[0] == userId
                && list[2] == passwd)
        {
            success =true;
            break;
        }
    }
    return success;
}
