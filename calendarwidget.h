#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "date.h"
#include "mybutton.h"

class DayLabel;

class CalendarWidget : public QWidget,public Date
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent=0);//构造函数

    static int selected;//被选择的日期标签的数组下标
    static int selectedDay;//被选择的日
    void jumpToDate(int,int,int);//跳转到指定日期
    friend class Widget;//声明友元类

signals:
    void signalDayClicked(int);//日期标签被点击信号
    void signalMonthChanged();//月切换信号

private:
    QVBoxLayout *verLayoutCalendar;//日历视图的垂直布局
    QWidget *widgetTitle;//标题栏
    QLabel *labelTitle;//标题标签
    MyButton *btnPrevMonth;//上月按钮
    MyButton *btnNextMonth;//下月按钮
    MyButton *btnLastYear;//上一年按钮
    MyButton *btnNextYear;//下一年按钮
    QHBoxLayout *horLayoutTitle;//标题栏的水平布局

    QWidget *widgetWeek;//星期栏
    DayLabel *labelWeek[7];//星期栏的7个标签
    QHBoxLayout *horLayoutWeek;//星期栏的水平布局

    QWidget *widgetBody;//日历主体
    DayLabel *labelDay[42];//日期标签数组
    QGridLayout *gridLayoutBody;//日期标签的网格布局

    void initDate();//初始化日期
    void initWidget();//初始化布局

private slots:
    void sltDayClicked(int);//日期标签点击槽函数
    void sltShowPrevMonth();//显示上月槽函数
    void sltShowNextMonth();//显示下月槽函数
    void sltShowLastYear();//显示上一年槽函数
    void sltShowNextYear();//显示下一年槽函数
};

#endif // CALENDARWIDGET_H
