#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QFile>


class Utils
{
public:
    Utils();
    static bool verifyPasswd(QFile& fileIn,QString& userId,QString passwd);
};

#endif // UTILS_H
