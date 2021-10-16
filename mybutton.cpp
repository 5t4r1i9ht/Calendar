#include "mybutton.h"

MyButton::MyButton(QWidget *parent):QPushButton(parent){}

bool MyButton::event(QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {

        QKeyEvent *ke = (QKeyEvent *)(e);
        if (ke->key() == Qt::Key_Up)
        {
            return false;
        }
        else if(ke->key()==Qt::Key_Down)
        {
            return false;
        }
        else if(ke->key()==Qt::Key_Left)
        {
            return false;
        }
        else if(ke->key()==Qt::Key_Right)
        {
            return false;
        }
    }
    return QWidget::event(e);
}
