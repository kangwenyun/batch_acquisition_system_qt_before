#ifndef SESSION_H
#define SESSION_H

#include <QString>

class Session
{
public:
    static Session* getInstance();
    void setUserId(QString id);
    QString getUserId();
private:
    Session();
    ~Session();
    //把复制构造函数和=操作符也设为私有，防止被复制
    Session(const Session&);
    Session& operator =(const Session&);

    QString userId;
};

#endif // CURRENTPERSON_H
