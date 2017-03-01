#include "session.h"
#include <QString>

Session::Session(){}

Session::~Session(){}

Session::Session(const Session&){}

Session& Session::operator =(const Session&){}

Session* Session::getInstance(){
    static Session* cperson = new Session(); //static就第一次执行第二次不执行了
    return cperson;
}

void Session::setUserId(QString id)
{
    if(NULL == userId)
    {
        userId = id;
    }
}

QString Session::getUserId()
{
    return userId;
}
