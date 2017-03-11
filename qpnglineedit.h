#ifndef QPNGLINEEDIT_H
#define QPNGLINEEDIT_H

#include <QPushButton>
#include <QLineEdit>
#include <QString>


class QPngLineEdit : public QPushButton
{
    Q_OBJECT

public:
    explicit QPngLineEdit(const QString &text, QLineEdit *edit, const QString &strImg,int flag);//1图标居左,0图标居右
};


#endif // QPNGLINEEDIT_H
