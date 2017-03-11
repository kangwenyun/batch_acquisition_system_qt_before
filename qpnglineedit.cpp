#include "qpnglineedit.h"

#include <QLineEdit>
#include <QHBoxLayout>

QPngLineEdit::QPngLineEdit(const QString &text, QLineEdit *edit, const QString &strImg, int flag)
: QPushButton(text, edit)
{
    QSize size = QSize(25, 25);
    setMinimumSize(size);
    setMaximumSize(size); // 设置按钮的大小为图片的大小
    setFocusPolicy(Qt::NoFocus); // 得到焦点时，不显示虚线框
    setFlat(true);
    setText(text);
    setCursor(QCursor(Qt::PointingHandCursor));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    if(!flag){
        buttonLayout->setContentsMargins(0,0,-5,0);
        buttonLayout->addStretch();
    }
    buttonLayout->addWidget(this);
    if(flag){
        buttonLayout->setContentsMargins(5,0,0,0);
        buttonLayout->addStretch();
    }
    edit->setLayout(buttonLayout);

    // 设置输入框中文件输入区，不让输入的文字在被隐藏在按钮下
    edit->setTextMargins(size.width(), 1, 1 , 1);

    // 设置style 图片位置url改为自己的。
    QString qss = QString(".QPngLineEdit{\
                          border-image: url(:/images/%1);\
                      }").arg(strImg);

    setStyleSheet(qss);
}
