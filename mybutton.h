#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QKeyEvent>
class MyButton : public QPushButton
{
public:
    explicit MyButton(QWidget *parent=0);//构造函数
    bool event(QEvent *e);//重写QPushButton的event函数
};

#endif // MYBUTTON_H
