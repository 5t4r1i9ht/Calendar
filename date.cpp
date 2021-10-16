#ifndef DATE_CPP
#define DATE_CPP
#include "date.h"
#include <QDebug>

QString Week[] = {"日","一", "二", "三", "四", "五", "六"};//星期

QString SolarHoliday[] = {"元旦", "情人节", "妇女节", "植树节", "权益日", "愚人节", "劳动节", "青年节", "护士节", "儿童节", "建党节", "建军节", "教师节", "国庆节", "平安夜", "圣诞节"};//公历节日
QString SolarTerm[] = {"小寒", "大寒", "立春", "雨水", "惊蛰", "春分", "清明", "谷雨", "立夏", "小满", "芒种", "夏至", "小暑", "大暑", "立秋", "处暑", "白露", "秋分", "寒露", "霜降", "立冬", "小雪", "大雪", "冬至"};//节气

QString LunarFestival[] = {"春节", "元宵节", "端午节", "七夕节", "中元节", "中秋节", "重阳节", "腊八节", "小年", "除夕"};//农历节日

QString TianGan[] = {"甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"};//天干
QString DiZhi[] = {"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"};//地支
QString ShengXiao[] = {"鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪"};//生肖

QString LunarCalendarDay[] = {"*", "初一", "初二", "初三", "初四", "初五",
                              "初六", "初七", "初八", "初九", "初十",
                              "十一", "十二", "十三", "十四", "十五",
                              "十六", "十七", "十八", "十九", "二十",
                              "廿一", "廿二", "廿三", "廿四", "廿五",
                              "廿六", "廿七", "廿八", "廿九", "三十"};//农历日
QString LunarCalendarMonth[] = {"*", "正", "二", "三", "四", "五", "六", "七", "八", "九", "十", "冬", "腊"};//农历月

int LunarCalendarTable[199] =
{
    0x04AE53, 0x0A5748, 0x5526BD, 0x0D2650, 0x0D9544, 0x46AAB9, 0x056A4D, 0x09AD42, 0x24AEB6, 0x04AE4A, /*1901-1910*/
    0x6A4DBE, 0x0A4D52, 0x0D2546, 0x5D52BA, 0x0B544E, 0x0D6A43, 0x296D37, 0x095B4B, 0x749BC1, 0x049754, /*1911-1920*/
    0x0A4B48, 0x5B25BC, 0x06A550, 0x06D445, 0x4ADAB8, 0x02B64D, 0x095742, 0x2497B7, 0x04974A, 0x664B3E, /*1921-1930*/
    0x0D4A51, 0x0EA546, 0x56D4BA, 0x05AD4E, 0x02B644, 0x393738, 0x092E4B, 0x7C96BF, 0x0C9553, 0x0D4A48, /*1931-1940*/
    0x6DA53B, 0x0B554F, 0x056A45, 0x4AADB9, 0x025D4D, 0x092D42, 0x2C95B6, 0x0A954A, 0x7B4ABD, 0x06CA51, /*1941-1950*/
    0x0B5546, 0x555ABB, 0x04DA4E, 0x0A5B43, 0x352BB8, 0x052B4C, 0x8A953F, 0x0E9552, 0x06AA48, 0x6AD53C, /*1951-1960*/
    0x0AB54F, 0x04B645, 0x4A5739, 0x0A574D, 0x052642, 0x3E9335, 0x0D9549, 0x75AABE, 0x056A51, 0x096D46, /*1961-1970*/
    0x54AEBB, 0x04AD4F, 0x0A4D43, 0x4D26B7, 0x0D254B, 0x8D52BF, 0x0B5452, 0x0B6A47, 0x696D3C, 0x095B50, /*1971-1980*/
    0x049B45, 0x4A4BB9, 0x0A4B4D, 0xAB25C2, 0x06A554, 0x06D449, 0x6ADA3D, 0x0AB651, 0x093746, 0x5497BB, /*1981-1990*/
    0x04974F, 0x064B44, 0x36A537, 0x0EA54A, 0x86B2BF, 0x05AC53, 0x0AB647, 0x5936BC, 0x092E50, 0x0C9645, /*1991-2000*/
    0x4D4AB8, 0x0D4A4C, 0x0DA541, 0x25AAB6, 0x056A49, 0x7AADBD, 0x025D52, 0x092D47, 0x5C95BA, 0x0A954E, /*2001-2010*/
    0x0B4A43, 0x4B5537, 0x0AD54A, 0x955ABF, 0x04BA53, 0x0A5B48, 0x652BBC, 0x052B50, 0x0A9345, 0x474AB9, /*2011-2020*/
    0x06AA4C, 0x0AD541, 0x24DAB6, 0x04B64A, 0x69573D, 0x0A4E51, 0x0D2646, 0x5E933A, 0x0D534D, 0x05AA43, /*2021-2030*/
    0x36B537, 0x096D4B, 0xB4AEBF, 0x04AD53, 0x0A4D48, 0x6D25BC, 0x0D254F, 0x0D5244, 0x5DAA38, 0x0B5A4C, /*2031-2040*/
    0x056D41, 0x24ADB6, 0x049B4A, 0x7A4BBE, 0x0A4B51, 0x0AA546, 0x5B52BA, 0x06D24E, 0x0ADA42, 0x355B37, /*2041-2050*/
    0x09374B, 0x8497C1, 0x049753, 0x064B48, 0x66A53C, 0x0EA54F, 0x06B244, 0x4AB638, 0x0AAE4C, 0x092E42, /*2051-2060*/
    0x3C9735, 0x0C9649, 0x7D4ABD, 0x0D4A51, 0x0DA545, 0x55AABA, 0x056A4E, 0x0A6D43, 0x452EB7, 0x052D4B, /*2061-2070*/
    0x8A95BF, 0x0A9553, 0x0B4A47, 0x6B553B, 0x0AD54F, 0x055A45, 0x4A5D38, 0x0A5B4C, 0x052B42, 0x3A93B6, /*2071-2080*/
    0x069349, 0x7729BD, 0x06AA51, 0x0AD546, 0x54DABA, 0x04B64E, 0x0A5743, 0x452738, 0x0D264A, 0x8E933E, /*2081-2090*/
    0x0D5252, 0x0DAA47, 0x66B53B, 0x056D4F, 0x04AE45, 0x4A4EB9, 0x0A4D4C, 0x0D1541, 0x2D92B5            /*2091-2099*/
};//农历打表
int MonthAdd[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};


Date::Date(int y=1901,int m=01,int d=01):QDate(y,m,d)
{
    initDate();//初始化日期
}

Date::Date(Date &d) : QDate(d.year(),d.month(),d.day()){}//复制构造函数

void Date::initDate()
{
    lunarCalendarDay=0;
    calendarWeek.clear();
    solarHoliday1.clear();
    solarHoliday2.clear();
    solarTerm.clear();
    lunarYear.clear();
    lunarMonth.clear();
    lunarDay.clear();
    lunarFestival.clear();
    //各字符串的初始化
    getCalendarWeek();
    getSolarHoliday();
    getSolarTerm();
    getLunarMonthAndDay();
    getLunarYear();
    getLunarFestival();
    //获取各字符串的内容
}

QString Date::_getSolarHoliday1()
{
    return solarHoliday1;
}

QString Date::_getSolarHoliday2()
{
    return solarHoliday2;
}

QString Date::_getSolarTerm()
{
    return solarTerm;
}

QString Date::_getLunarYear()
{
    return lunarYear;
}

QString Date::_getLunarMonth()
{
    return lunarMonth;
}

QString Date::_getLunarDay()
{
    return lunarDay;
}

QString Date::_getLunarFestival()
{
    return lunarFestival;
}

int Date::getCumulativeDays()
{
    int sum = 0;
    for (int i = 1; i < month(); i++)
    {
        sum += daysOfMonth(i);
    }
    sum += day();
    return sum;
}

int Date::getCumulativeDaysFrom19000100()
{
    int sum = 0;
    for (int i = 1900; i < year(); i++)
    {
        if (isLeapYear(i))
        {
            sum += 366;
        }
        else
        {
            sum += 365;
        }
    }
    sum += getCumulativeDays();
    return sum;
}

int Date::getWeekOfFirstDayInMonth()
{
    return ((year() - 1) + (year() - 1) / 4 - (year() - 1) / 100 + (year() - 1) / 400 + getCumulativeDays() - day() + 1) % 7;//根据公式获取当月1日的星期
}

int Date::getThSun(int i)
{
    int days = 1, th = 0, weekOfFirstDayOfMonth = getWeekOfFirstDayInMonth();
    if (weekOfFirstDayOfMonth == 0)
    {
        th++;
    }
    else
    {
        days += 7 - weekOfFirstDayOfMonth;
        th++;
    }
    while (th < i)
    {
        days += 7;
        th++;
    }
    return days;
}

void Date::getCalendarWeek()
{
    int _week = dayOfWeek()%7;
    calendarWeek.append(Week[_week]);
}

QString Date::_getCalendarWeek()
{
    return calendarWeek;
}

int Date::daysOfMonth(int _month)
{
    switch (_month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
    {
        if (isLeapYear(year()))
        {
            return 29;
        }
        return 28;
    }
    default:
        return 0;
    }
}

void Date::getSolarHoliday()
{
    int _month = month(), _day = day();
    switch (_month)
    {
    case 1:
    {
        if (_day == 1)
        {
            solarHoliday1.append(SolarHoliday[0]);
            return;
        }
    }
        break;
    case 2:
    {
        if (_day == 14)
        {
            solarHoliday1.append(SolarHoliday[1]);
        }
    }
        break;
    case 3:
    {
        if (_day == 8)
        {
            solarHoliday1.append(SolarHoliday[2]);
            return;
        }
        else if (_day == 12)
        {
            solarHoliday1.append(SolarHoliday[3]);
            return;
        }
        else if (_day == 15)
        {
            solarHoliday1.append(SolarHoliday[4]);
            return;
        }
    }
        break;
    case 4:
    {
        if (_day == 1)
        {
            solarHoliday1.append(SolarHoliday[5]);
            return;
        }
    }
        break;
    case 5:
    {
        if (_day == 1)
        {
            solarHoliday1.append(SolarHoliday[6]);
        }
        else if (_day == 4)
        {
            solarHoliday1.append(SolarHoliday[7]);
        }
        else if (_day == 12)
        {
            solarHoliday1.append(SolarHoliday[8]);
        }
        if (_day == getThSun(2))
        {
            solarHoliday2.append("母亲节");
            return;
        }
    }
        break;
    case 6:
    {
        if (_day == 1)
        {
            solarHoliday1.append(SolarHoliday[9]);
            return;
        }
        else if (_day == getThSun(3))
        {
            solarHoliday2.append("父亲节");
            return;
        }
    }
        break;
    case 7:
    {
        if (_day == 1)
        {
            solarHoliday1.append(SolarHoliday[10]);
            return;
        }
    }
        break;
    case 8:
    {
        if (_day == 1)
        {
            solarHoliday1.append(SolarHoliday[11]);
            return;
        }
    }
        break;
    case 9:
    {
        if (_day == 10)
        {
            solarHoliday1.append(SolarHoliday[12]);
            return;
        }
    }
        break;
    case 10:
    {
        if (_day == 1)
        {
            solarHoliday1.append(SolarHoliday[13]);
            return;
        }
    }
        break;
    case 12:
    {
        if (_day == 24)
        {
            solarHoliday1.append(SolarHoliday[14]);
            return;
        }
        else if (_day == 25)
        {
            solarHoliday1.append(SolarHoliday[15]);
            return;
        }
    }
        break;
    }
}

int Date::getCumulativeDaysOfSolarTerm(int thSolarTerm)
{
    return 365.242 * (year()-1900) + 6.2 + 15.22 * thSolarTerm - 1.9 * sin(0.262 * thSolarTerm);//根据公式获取第i个节气在当年中的第几天
}

void Date::getSolarTerm()
{
    for (int i = 0; i < 24; i++)
    {
        if (getCumulativeDaysFrom19000100() == getCumulativeDaysOfSolarTerm(i))
        {
            solarTerm.append(SolarTerm[i]);
            break;
        }
    }
}

//网上找的农历算法
int Date::getLunarCalendarDay()
{
    lunarCalendarDay=0;
    int _year=year(),_month=month(),_day=day();
    int Spring_NY, Sun_NY, StaticDayCount;
    int index, flag;
    //Spring_NY 记录春节离当年元旦的天数。
    //Sun_NY 记录阳历日离当年元旦的天数。
    if (((LunarCalendarTable[_year - 1901] & 0x0060) >> 5) == 1)
        Spring_NY = (LunarCalendarTable[_year - 1901] & 0x001F) - 1;
    else
        Spring_NY = (LunarCalendarTable[_year - 1901] & 0x001F) - 1 + 31;
    Sun_NY = MonthAdd[_month - 1] + _day - 1;
    if ((!(_year % 4)) && (_month > 2))
        Sun_NY++;
    //StaticDayCount记录大小月的天数 29 或30
    //index 记录从哪个月开始来计算。
    //flag 是用来对闰月的特殊处理。
    //判断阳历日在春节前还是春节后
    if (Sun_NY >= Spring_NY) //阳历日在春节后（含春节那天）
    {
        Sun_NY -= Spring_NY;
        _month = 1;
        index = 1;
        flag = 0;
        if ((LunarCalendarTable[_year - 1901] & (0x80000 >> (index - 1))) == 0)
            StaticDayCount = 29;
        else
            StaticDayCount = 30;
        while (Sun_NY >= StaticDayCount)
        {
            Sun_NY -= StaticDayCount;
            index++;
            if (_month == ((LunarCalendarTable[_year - 1901] & 0xF00000) >> 20))
            {
                flag = ~flag;
                if (flag == 0)
                    _month++;
            }
            else
                _month++;
            if ((LunarCalendarTable[_year - 1901] & (0x80000 >> (index - 1))) == 0)
                StaticDayCount = 29;
            else
                StaticDayCount = 30;
        }
        _day = Sun_NY + 1;
    }
    else //阳历日在春节前
    {
        Spring_NY -= Sun_NY;
        _year--;
        _month = 12;
        if (((LunarCalendarTable[_year - 1901] & 0xF00000) >> 20) == 0)
            index = 12;
        else
            index = 13;
        flag = 0;
        if ((LunarCalendarTable[_year - 1901] & (0x80000 >> (index - 1))) == 0)
            StaticDayCount = 29;
        else
            StaticDayCount = 30;
        while (Spring_NY > StaticDayCount)
        {
            Spring_NY -= StaticDayCount;
            index--;
            if (flag == 0)
                _month--;
            if (_month == ((LunarCalendarTable[_year - 1901] & 0xF00000) >> 20))
                flag = ~flag;
            if ((LunarCalendarTable[_year - 1901] & (0x80000 >> (index - 1))) == 0)
                StaticDayCount = 29;
            else
                StaticDayCount = 30;
        }
        _day = StaticDayCount - Spring_NY + 1;
    }
    lunarCalendarDay |= _day;
    lunarCalendarDay |= (_month << 6);
    if (_month == ((LunarCalendarTable[_year - 1901] & 0xF00000) >> 20))
        return 1;
    else
        return 0;
}

void Date::getLunarYear()
{
    int _year = year(), _month = month();
    if (_month > 2 || ((lunarCalendarDay & 0x3C0) >> 6) <= 2)
    {
        lunarYear.append(TianGan[abs(_year - 2000 + 6) % 10]);
        lunarYear.append(DiZhi[abs(_year - 2000 + 4) % 12]);
        lunarYear.append(ShengXiao[abs(_year - 2000 + 4) % 12]);
        lunarYear.append("年");
    }
    else
    {
        lunarYear.append(TianGan[abs(_year - 2000 + 5) % 10]);
        lunarYear.append(DiZhi[abs(_year - 2000 + 3) % 12]);
        lunarYear.append(ShengXiao[abs(_year - 2000 + 3) % 12]);
        lunarYear.append("年");
    }
}

void Date::getLunarMonthAndDay()
{
    if (getLunarCalendarDay())
    {
        lunarMonth.append("闰");
        lunarMonth.append(LunarCalendarMonth[(lunarCalendarDay & 0x3C0) >> 6]);
    }
    else
        lunarMonth.append(LunarCalendarMonth[(lunarCalendarDay & 0x3C0) >> 6]);
    lunarMonth.append("月");
    lunarDay.append(LunarCalendarDay[(lunarCalendarDay & 0x3F)]);
}

void Date::getLunarFestival()
{
    int _lunarMonth = (lunarCalendarDay & 0x3C0) >> 6;
    int _lunarDay = lunarCalendarDay & 0x3F;

    switch (_lunarMonth)
    {
    case 1:
    {
        if (_lunarDay == 1)
        {
            lunarFestival.append(LunarFestival[0]);
            return;
        }
        else if (_lunarDay == 15)
        {
            lunarFestival.append(LunarFestival[1]);
            return;
        }
    }
        break;
    case 5:
    {
        if (_lunarDay == 5)
        {
            lunarFestival.append(LunarFestival[2]);
            return;
        }
    }
        break;
    case 7:
    {
        if (_lunarDay == 7)
        {
            lunarFestival.append(LunarFestival[3]);
            return;
        }
        else if (_lunarDay == 15)
        {
            lunarFestival.append(LunarFestival[4]);
            return;
        }
    }
        break;
    case 8:
    {
        if (_lunarDay == 15)
        {
            lunarFestival.append(LunarFestival[5]);
            return;
        }
    }
        break;
    case 9:
    {
        if (_lunarDay == 9)
        {
            lunarFestival.append(LunarFestival[6]);
            return;
        }
    }
        break;
    case 12:
    {
        if (_lunarDay == 8)
        {
            lunarFestival.append(LunarFestival[7]);
            return;
        }
        else if (_lunarDay == 24)
        {
            lunarFestival.append(LunarFestival[8]);
            return;
        }
    }
        break;
    default:
    {
        break;
    }
    }

    //判断除夕
    if (_lunarMonth >= 12 && (_lunarDay >= 29))
    {
        QDate tempDate(year(),month(),day());
        tempDate=tempDate.addDays(1);
        Date tempDate2(tempDate.year(),tempDate.month(),tempDate.day());
        tempDate2.getLunarCalendarDay();
        int LunarMonthOfNextDay = (tempDate2.lunarCalendarDay & 0x3C0) >> 6;
        int nextLunarDay = tempDate2.lunarCalendarDay & 0x3F;

        if (LunarMonthOfNextDay == 1 && nextLunarDay == 1)
        {
            lunarFestival.append(LunarFestival[9]);
            return;
        }
    }
}

bool Date::judgeHoliday()
{
    if(solarHoliday2!=""||solarHoliday1!=""||lunarFestival!=""||solarTerm!="")
    {
        return true;
    }
    return false;
}

QString Date::_getHoliday()
{
    QString holiday="";
    int count=0;
    if(lunarFestival!="")
    {
        holiday.append(lunarFestival);
        count++;
    }
    if(solarHoliday2!="")
    {
        if(count)
        {
            holiday.append(" ");
        }
        holiday.append(solarHoliday2);
        count++;
    }
    if(solarHoliday1!="")
    {
        if(count)
        {
            holiday.append(" ");
        }
        holiday.append(solarHoliday1);
        count++;
    }
    if(solarTerm!="")
    {
        if(count)
        {
            holiday.append(" ");
        }
        holiday.append(solarTerm);
        count++;
    }
    return holiday;
}

#endif
