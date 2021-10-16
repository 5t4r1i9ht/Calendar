#ifndef DAYLABEL_H
#define DAYLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QFile>
#include <QDir>
#include "date.h"

class DayLabel : public QLabel,public Date
{
    Q_OBJECT

public:
    explicit DayLabel(QWidget *parent=0);//构造函数
    void setColor();//设置日期标签颜色
    void showDay();//显示节日或节气或农历日
    bool isNotePadExist();//判断日期标签对应的日期对应的记事本是否存在
private:
    void enterEvent(QEvent*);//鼠标进入日期标签事件
    void leaveEvent(QEvent*);//鼠标离开日期标签事件
    void mousePressEvent(QMouseEvent*);//鼠标点击日期标签事件

signals:
    void signalClicked(int);//点击信号
};

#endif // DAYLABEL_H
