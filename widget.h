#ifndef WIDGET_H
#define WIDGET_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QFile>
#include <QDir>
#include "calendarwidget.h"
#include "mybutton.h"

class Widget:public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);//构造函数

private:
    void initWidget();//初始化布局
    void initStyle();//初始化样式
    void displayText();//文本框显示文字
    void saveText();//保存文本框文字到文件

    QVBoxLayout *verlayoutWidgetDetails;//信息栏垂直布局
    QHBoxLayout *horlayoutWidgetBottom;//记录控制栏水平布局
    QVBoxLayout *verlayoutWidgetRight;//侧边栏垂直布局
    QHBoxLayout *horLayoutWidget;//日历视图与侧边栏的水平布局
    CalendarWidget *calendar;//日历视图

    QDir *dir;//文件保存路径
    QWidget *widgetRight;//侧边栏
    QWidget *widgetDetails;//信息栏
    QWidget *widgetBottom;//记录控制栏
    MyButton *btnBack;//回到今天按钮
    QLabel *labelShowDate;//日期显示标签
    QLabel *labelShowDay;//放大日期显示标签
    QLabel *labelShowLunarYear;//天干地支年显示标签
    QLabel *labelShowLunarMonthAndDay;//农历日月显示标签
    QLabel *labelShowHoliday;//节假日显示标签
    QPlainTextEdit *notepad;//文本框
    QFile *aFile;//文件读取
    MyButton *btnClear;//清除按钮
    MyButton *btnSave;//保存按钮

//    void wheelEvent(QWheelEvent *e);//鼠标滑轮事件
    void keyPressEvent(QKeyEvent *e);//键盘点击事件

private slots:

    void sltBackToToday();//返回今天槽函数
    void sltDayClicked(int);//日期点击槽函数
    void sltMonthChanged();//月份切换槽函数
    void sltClear();//清除槽函数
    void sltSave();//保存槽函数
};

#endif // WIDGET_H
