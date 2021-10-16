#include <QString>
#include <QDate>

#ifndef DATE_H
#define DATE_H

class Date:public QDate
{
private:
    int lunarCalendarDay;//获取农历的中间变量
    QString calendarWeek,solarHoliday1,solarHoliday2,solarTerm,lunarYear,lunarMonth,lunarDay,lunarFestival;//字符串对象的星期、公历节假日1、公历节假日2、节气、农历年、农历月、农历日、农历节日
public:
    Date(int,int,int);//构造函数
    explicit Date(Date &);//复制构造函数
    void initDate();//日期初始化，用于获取
    void getSolarHoliday();//获取公历节假日
    int getCumulativeDaysOfSolarTerm(int);//获取第i个节气在当年的积日
    void getSolarTerm();//获取节气
    int getLunarCalendarDay();//获取农历的中间变量
    void getLunarMonthAndDay();//获取农历月和日
    void getLunarYear();//获取天干地支
    void getLunarFestival();//获取农历节日
    int getCumulativeDays();//获取当日在当年的积日
    int getCumulativeDaysFrom19000100();//获取当日从1900年01月00日以来的积日
    int getThSun(int);//获取当月第i个星期日在当月的天数
    int getWeekOfFirstDayInMonth();//获取当月1日的星期
    void getCalendarWeek();//获取星期
    int daysOfMonth(int);//获取当月的天数
    bool judgeHoliday();//判断当日是否是节假日

    QString _getCalendarWeek();//返回星期（日~六）字符串
    QString _getSolarHoliday1();//返回公历节假日1字符串
    QString _getSolarHoliday2();//返回公历节假日2字符串
    QString _getSolarTerm();//返回节气字符串
    QString _getLunarYear();//返回天干地支字符串
    QString _getLunarMonth();//返回农历月字符串
    QString _getLunarDay();//返回农历日字符串
    QString _getLunarFestival();//返回农历节日字符串
    QString _getHoliday();//返回全部节日字符串
};

#endif // DATE_H
