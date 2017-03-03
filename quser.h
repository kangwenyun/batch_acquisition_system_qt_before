#ifndef QUSER_H
#define QUSER_H
#include <QString>
class Quser
{
public:
    Quser();
    Quser(QString m_userid,QString m_username,QString m_passwd,QString m_age,QString m_sex,QString m_job,QString m_level);
    QString userid;
    QString username;
    QString passwd;
    QString age;
    QString sex;
    QString job;
    QString level;


};

#endif // QUSER_H
