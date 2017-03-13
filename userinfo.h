#ifndef USERINFO_H
#define USERINFO_H
#include<QString>
class UserInfo
{
public:
    UserInfo();
    UserInfo(QString m_userid,QString m_username);
    QString userid;
    QString username;
    QString level;
};

#endif // USERINFO_H
