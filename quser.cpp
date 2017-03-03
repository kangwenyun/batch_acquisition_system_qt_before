#include "quser.h"

Quser::Quser(){}
Quser::Quser(QString m_userid,QString m_username,QString m_passwd,QString m_age,QString m_sex,QString m_job,QString m_level)
{
    userid=m_userid;
    username=m_username;
    passwd=m_passwd;
    age=m_age;
    sex=m_sex;
    job=m_job;
    level=m_level;
}
