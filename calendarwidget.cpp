#ifndef CALENDARWIDGET_CPP
#define CALENDARWIDGET_CPP
#include "calendarwidget.h"
#include "date.cpp"
#include "daylabel.cpp"

int CalendarWidget::selected=-1;//初始化为-1
int CalendarWidget::selectedDay=-1;//初始化为-1

CalendarWidget::CalendarWidget(QWidget *parent):QWidget(parent),Date(Date::currentDate().year(),Date::currentDate().month(),Date::currentDate().day())
{
    selectedDay=day();//默认被选择日期为当日
    initWidget();
    initDate();
}

void CalendarWidget::jumpToDate(int _year,int _month,int _day)
{
    this->setDate(_year,_month,_day);//设置日期
    initDate();
}

void CalendarWidget::initWidget()
{
    this->setMinimumSize(440,380);//设置日历视图的最小尺寸
    this->setObjectName("widgetCalendar");

    widgetTitle = new QWidget(this);
    widgetTitle->setMaximumHeight(50);//设置标题栏的最大尺寸

    //设置四个按钮的文字、样式、最大高度
    btnLastYear = new MyButton(widgetTitle);
    btnLastYear->setText(QString("上一年"));
    btnLastYear->setStyleSheet("font:20px;font-family:microsoft yahei");
    btnLastYear->setMinimumHeight(30);

    btnPrevMonth = new MyButton(widgetTitle);
    btnPrevMonth->setText(QString("上月"));
    btnPrevMonth->setStyleSheet("font:20px;font-family:microsoft yahei");
    btnPrevMonth->setMinimumHeight(30);

    labelTitle = new QLabel(widgetTitle);
    labelTitle->setAlignment(Qt::AlignCenter);
    labelTitle->setObjectName("labelTitle");
    labelTitle->setStyleSheet("font:20px;font-family:microsoft yahei");
    labelTitle->setMinimumHeight(30);

    btnNextMonth = new MyButton(widgetTitle);
    btnNextMonth->setText(QString("下月"));
    btnNextMonth->setStyleSheet("font:20px;font-family:microsoft yahei");
    btnNextMonth->setMinimumHeight(30);

    btnNextYear = new MyButton(widgetTitle);
    btnNextYear->setText(QString("下一年"));
    btnNextYear->setStyleSheet("font:20px;font-family:microsoft yahei");
    btnNextYear->setMinimumHeight(30);

    //新建标题栏水平布局，将标题栏组件添加到标题栏水平布局
    horLayoutTitle = new QHBoxLayout(widgetTitle);
    horLayoutTitle->addWidget(btnLastYear);
    horLayoutTitle->addWidget(btnPrevMonth);
    horLayoutTitle->addWidget(labelTitle);
    horLayoutTitle->addWidget(btnNextMonth);
    horLayoutTitle->addWidget(btnNextYear);

    //将标题栏添加到日历视图的垂直布局
    verLayoutCalendar = new QVBoxLayout(this);
    verLayoutCalendar->addWidget(widgetTitle);

    //按钮点击信号与信号与对应槽函数的连接，点击按钮时执行相应槽函数
    connect(btnPrevMonth,SIGNAL(clicked(bool)),this,SLOT(sltShowPrevMonth()));
    connect(btnNextMonth,SIGNAL(clicked(bool)),this,SLOT(sltShowNextMonth()));
    connect(btnLastYear,SIGNAL(clicked(bool)),this,SLOT(sltShowLastYear()));
    connect(btnNextYear,SIGNAL(clicked(bool)),this,SLOT(sltShowNextYear()));

    //设置星期栏最小最大尺寸
    widgetWeek = new QWidget(this);
    widgetWeek->setMinimumHeight(30);
    widgetWeek->setMaximumHeight(40);

    //新建星期栏水平布局
    horLayoutWeek = new QHBoxLayout(widgetWeek);
    horLayoutWeek->setContentsMargins(0,0,0,0);
    horLayoutWeek->setSpacing(0);

    for(int i=0;i<7;i++)
    {
        labelWeek[i]=new DayLabel(widgetWeek);
        labelWeek[i]->setText(Week[i]);//设置星期栏的星期标签的文字（日~六）
        //设置星期栏的样式，周末背景颜色为浅红色，字体颜色为红色，其余背景颜色为白色，字体颜色为黑色
        if(i==0||i==6)
        {
            labelWeek[i]->setStyleSheet("background:#fff0f0;border:1px solid #c3c3c3;color:red;");
        }
        else
        {
            labelWeek[i]->setStyleSheet("background:#ffffff;border:1px solid #c3c3c3;color:#000000;");
        }
        labelWeek[i]->setMinimumHeight(0);
        labelWeek[i]->setAlignment(Qt::AlignCenter);//居中对齐
        horLayoutWeek->addWidget(labelWeek[i]);//将星期标签逐个添加到星期栏水平布局
    }

    //将星期栏添加到日历视图的垂直布局
    verLayoutCalendar->addWidget(widgetWeek);

    //新建日历视图主体并添加到日历视图的垂直布局
    widgetBody=new QWidget(this);
    verLayoutCalendar->addWidget(widgetBody);

    //新建日期标签的网格布局
    gridLayoutBody=new QGridLayout(widgetBody);
    gridLayoutBody->setHorizontalSpacing(0);
    gridLayoutBody->setVerticalSpacing(0);
    gridLayoutBody->setContentsMargins(0,0,0,0);

    for(int i=0;i<42;i++)
    {
        labelDay[i]=new DayLabel(widgetBody);
        labelDay[i]->setObjectName("labelDay");
        labelDay[i]->setAlignment(Qt::AlignCenter);
        if(i%7==0||i%7==6)
        {
            labelDay[i]->setProperty("type","Holiday");//为周末的日期标签设置type属性为Holiday
        }
        labelDay[i]->setProperty("num",i);//设置日期标签的属性num为i
        gridLayoutBody->addWidget(labelDay[i],i/7,i%7);//逐个将日期标签添加到网格布局
        connect(labelDay[i],SIGNAL(signalClicked(int)),this,SLOT(sltDayClicked(int)));//逐个将日期标签的点击信号与日期点击槽函数连接
    }
}

void CalendarWidget::initDate()
{
    //新建三个日期对象，分别为上月1日、本月1日和下月1日
    Date lastMonth(addMonths(-1).year(),addMonths(-1).month(),1);
    Date thisMonth(year(),month(),1);
    Date nextMonth(addMonths(1).year(),addMonths(1).month(),1);

    int daysOfThisMonth=daysOfMonth(thisMonth.month());//本月天数
    int daysOfLastMonth=lastMonth.daysOfMonth(lastMonth.month());//上月天数

    //设置标题标签的文字为本月年月
    QString strText=QDate::currentDate().toString("%1 年 %2 月").arg(thisMonth.year()).arg(thisMonth.month());
    labelTitle->setText(strText);

    //如果本月第一天的星期为星期天，则第一行显示上个月的日期
    if(thisMonth.dayOfWeek()%7==0)
    {
        //上月日期标签初始化
        for(int i=0;i<7;i++)
        {
            //为每个日期标签初始化
            labelDay[i]->setDate(lastMonth.year(),lastMonth.month(),daysOfLastMonth-6+i);
            labelDay[i]->initDate();
            labelDay[i]->showDay();
            labelDay[i]->setProperty("type","LastMonth");//设置日期标签的type属性为LastMonth
            labelDay[i]->setProperty("day",daysOfLastMonth-6+i);//设置日期标签的day属性
        }
        //下月日期标签初始化
        for(int i=0;i<(42-daysOfThisMonth-7);i++)
        {
            //为每个日期标签初始化
            labelDay[daysOfThisMonth+7+i]->setDate(nextMonth.year(),nextMonth.month(),i+1);
            labelDay[daysOfThisMonth+7+i]->initDate();
            labelDay[daysOfThisMonth+7+i]->showDay();
            labelDay[daysOfThisMonth+7+i]->setProperty("type","NextMonth");//设置日期标签的type属性为NextMonth
            labelDay[daysOfThisMonth+7+i]->setProperty("day",i+1);//设置日期标签的day属性
        }
    }
    else
    {
        //上月日期标签初始化
        for(int i=0;i<thisMonth.dayOfWeek();i++)
        {
            //为每个日期标签初始化
            labelDay[i]->setDate(lastMonth.year(),lastMonth.month(),daysOfLastMonth-thisMonth.dayOfWeek()+i+1);
            labelDay[i]->initDate();
            labelDay[i]->showDay();
            labelDay[i]->setProperty("type","LastMonth");//设置日期标签的type属性为LastMonth
            labelDay[i]->setProperty("day",daysOfLastMonth-thisMonth.dayOfWeek()+i+1);//设置日期标签的day属性
        }
        //下月日期标签初始化
        for(int i=(thisMonth.dayOfWeek()+daysOfThisMonth);i<42;i++)
        {
            //为每个日期标签初始化
            labelDay[i]->setDate(nextMonth.year(),nextMonth.month(),i-thisMonth.dayOfWeek()-daysOfThisMonth+1);
            labelDay[i]->initDate();
            labelDay[i]->showDay();
            labelDay[i]->setProperty("type","NextMonth");//设置日期标签的type属性为NextMonth
            labelDay[i]->setProperty("day",i-thisMonth.dayOfWeek()-daysOfThisMonth+1);//设置日期标签的day属性
        }
    }

    //本月日期标签初始化
    int index=0;
    for(int i=thisMonth.dayOfWeek();i<(thisMonth.dayOfWeek()+daysOfThisMonth);i++)
    {
        index=((thisMonth.dayOfWeek())==0)?(i+7):i;//根据本月第一天的星期控制开始显示本月日期
        //初始化
        labelDay[index]->setDate(this->year(),this->month(),i-thisMonth.dayOfWeek()+1);
        labelDay[index]->initDate();
        labelDay[index]->setProperty("type","CommonDay");//日期标签的type属性默认为CommonDay
        if(i%7==0||i%7==6)//如果是周末
        {
            labelDay[index]->setProperty("type","Holiday");//设置日期标签的type属性为Holiday
        }
        else if(labelDay[index]->judgeHoliday())//如果是节日
        {
            labelDay[index]->setProperty("type","Holiday");//设置日期标签的type属性为Holiday
        }

        if(labelDay[index]->day()==selectedDay)//如果该日期标签对应的日期被选中
        {
            selected=index;//更新selected
        }
        if(labelDay[index]->year()==QDate::currentDate().year()&&labelDay[index]->month()==QDate::currentDate().month()&&labelDay[index]->day()==QDate::currentDate().day())
        {
            labelDay[index]->setProperty("type","CurrentDay");//如果该日期标签对应的日期就是今天，设置其type属性为CurrentDay
        }
        labelDay[index]->showDay();//显示节日或节气或农历日/月
    }
    for(int i=0;i<42;i++)
    {
        labelDay[i]->setColor();//设置日期标签的颜色
    }
    Q_EMIT signalMonthChanged();//发射月份切换的信号
}

void CalendarWidget::sltDayClicked(int _num)
{
    if(_num<0)//如果传来的日期标签数组的下标小于0
    {
        QDate tempDate=this->addMonths(-1);
        int dayOfLastMonth=tempDate.daysInMonth();
        selectedDay=labelDay[_num+7]->day()+dayOfLastMonth-7;//更新被选择日期
        sltShowPrevMonth();//显示上月
    }
    else if(_num>41)//如果传来的日期标签数组的下标大于0
    {
        int dayOfThisMonth=daysInMonth();
        selectedDay=(labelDay[_num-7]->day()+7)%dayOfThisMonth;
        sltShowNextMonth();//显示下月
    }
    else if(labelDay[_num]->property("type").toString()=="LastMonth")//如果被点击日期标签为上月
    {
        selectedDay=labelDay[_num]->day();
        sltShowPrevMonth();//显示上月
    }
    else if(labelDay[_num]->property("type").toString()=="NextMonth")//如果被点击日期标签为下月
    {
        selectedDay=labelDay[_num]->day();
        sltShowNextMonth();//显示下月
    }
    else
    {
        //如果被点击日期在本月
        //更新被选择日期、下标
        selectedDay=labelDay[_num]->day();
        if(selected!=-1)
        {
            labelDay[selected]->setColor();
        }
        selected=_num;
        labelDay[_num]->setColor();//更新被选中日期标签的样式
        Q_EMIT signalDayClicked(_num);//发射日期点击信号
    }
}

void CalendarWidget::sltShowLastYear()
{
    QDate tempDate=this->addYears(-1);
    if(selectedDay>tempDate.daysInMonth())//显示上一年时，如果被选择日期大于上年对应月的天数
    {
        selectedDay=tempDate.daysInMonth();//则被选择日期为上年对应月的天数
    }
    this->setDate(tempDate.year(),tempDate.month(),selectedDay);
    initDate();//初始化日期
}

void CalendarWidget::sltShowPrevMonth()
{
    QDate tempDate=this->addMonths(-1);
    if(selectedDay>tempDate.daysInMonth())
    {
        selectedDay=tempDate.daysInMonth();
    }
    this->setDate(tempDate.year(),tempDate.month(),selectedDay);
    initDate();//注释类比上面
}

void CalendarWidget::sltShowNextMonth()
{
    QDate tempDate=this->addMonths(1);
    if(selectedDay>tempDate.daysInMonth())
    {
        selectedDay=tempDate.daysInMonth();
    }
    this->setDate(tempDate.year(),tempDate.month(),selectedDay);
    initDate();
}

void CalendarWidget::sltShowNextYear()
{
    QDate tempDate=this->addYears(1);
    if(selectedDay>tempDate.daysInMonth())
    {
        selectedDay=tempDate.daysInMonth();
    }
    this->setDate(tempDate.year(),tempDate.month(),selectedDay);
    initDate();
}

#endif
