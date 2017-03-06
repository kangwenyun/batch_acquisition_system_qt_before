#ifndef LOGER_H
#define LOGER_H
#include <QString>
class Loger
{
public:
    Loger();
    static Loger* getInstance();
    void setLoger(QString user,QString operation);
private:
    ~Loger();
    //把复制构造函数和=操作符也设为私有，防止被复制
    //Loger(const Loger&);
  //  Loger& operator =(const Loger&);
};

#endif // LOGER_H
