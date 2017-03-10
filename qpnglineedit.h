#ifndef QPNGLINEEDIT_H
#define QPNGLINEEDIT_H

#include <QPushButton>
#include <QLineEdit>
#include <QString>


class QPngLineEdit : public QPushButton
{
    Q_OBJECT

public:
    explicit QPngLineEdit(const QString &text, QLineEdit *edit, const QString &strImg);
};


#endif // QPNGLINEEDIT_H
