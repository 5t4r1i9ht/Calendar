#include "widget.h"
#include "daylabel.h"
#include <QDebug>
Widget::Widget(QWidget *parent):QWidget(parent)
{
    dir=new QDir(QDir::homePath().append('/').append("Documents"));//home目录下的Documents目录
    if(!dir->exists())//路径不存在
    {
        dir->mkdir(dir->path());//新建路径
    }
    dir->setPath(dir->path().append("/MyNotepad"));//Documents目录下的MyNotepad目录
    if(!dir->exists())//路径不存在
    {
        dir->mkdir(dir->path());//新建路径
    }
    initWidget();//初始化界面
    initStyle();//初始化样式
}

void Widget::initWidget()
{
    //设置主界面最小尺寸
    this->setMinimumSize(800,550);
    //新建日历视图
    calendar=new CalendarWidget(this);

    //新建侧边栏
    widgetRight=new QWidget(this);
    //新建信息栏及设置最小尺寸
    widgetDetails=new QWidget(widgetRight);
    widgetDetails->setMinimumWidth(125);

    //新建回到今天按钮、日期显示标签、日期放大显示标签、节假日显示标签、天干地支年显示标签、农历月日显示标签、文本框
    btnBack=new MyButton(widgetDetails);
    labelShowDate=new QLabel(widgetDetails);
    labelShowDay=new QLabel(widgetDetails);
    labelShowHoliday=new QLabel(widgetDetails);
    labelShowLunarYear=new QLabel(widgetDetails);
    labelShowLunarMonthAndDay=new QLabel(widgetDetails);
    notepad=new QPlainTextEdit(widgetDetails);

    //新建记录控制栏、清除按钮、保存按钮
    widgetBottom=new QWidget(widgetRight);
    btnClear=new MyButton(widgetBottom);
    btnSave=new MyButton(widgetBottom);

    //全部居中
    labelShowDate->setAlignment(Qt::AlignCenter);
    labelShowDay->setAlignment(Qt::AlignCenter);
    labelShowHoliday->setAlignment(Qt::AlignCenter);
    labelShowLunarYear->setAlignment(Qt::AlignCenter);
    labelShowLunarMonthAndDay->setAlignment(Qt::AlignCenter);

    //设置组件文字及样式
    btnBack->setText(QString("回到今天"));
    btnBack->setStyleSheet("font:18px;font-family:microsoft yahei");
    labelShowDate->setStyleSheet("font:18px;font-family:microsoft yahei");
    labelShowDate->setMaximumHeight(20);
    labelShowDay->setStyleSheet("background-color: #fb0;color: white; font: 64px;font-family:microsoft yahei;");
    labelShowDay->setMaximumHeight(125);
    labelShowHoliday->setMinimumHeight(30);
    labelShowLunarYear->setStyleSheet("font:18px;font-family:microsoft yahei");
    labelShowLunarYear->setMaximumHeight(20);
    labelShowLunarMonthAndDay->setStyleSheet("font:18px;font-family:microsoft yahei");
    labelShowLunarMonthAndDay->setMaximumHeight(20);
    notepad->setStyleSheet("font:14px;font-family:microsoft yahei");
    notepad->setMaximumWidth(200);
    btnClear->setText(QString("清除"));
    btnClear->setStyleSheet("font:18px;font-family:microsoft yahei");
    btnSave->setText(QString("保存"));
    btnSave->setStyleSheet("font:18px;font-family:microsoft yahei");

    //新建信息栏垂直布局，并将相关组件添加到其中
    verlayoutWidgetDetails=new QVBoxLayout(widgetDetails);
    verlayoutWidgetDetails->setContentsMargins(0,0,0,0);
    verlayoutWidgetDetails->setSpacing(0);
    verlayoutWidgetDetails->addWidget(btnBack);
    verlayoutWidgetDetails->addWidget(labelShowDate);
    verlayoutWidgetDetails->addWidget(labelShowDay);
    verlayoutWidgetDetails->addWidget(labelShowHoliday);
    verlayoutWidgetDetails->addWidget(labelShowLunarYear);
    verlayoutWidgetDetails->addWidget(labelShowLunarMonthAndDay);
    verlayoutWidgetDetails->addWidget(notepad);

    //新建记录控制栏水平布局，并将相关组件添加到其中
    horlayoutWidgetBottom=new QHBoxLayout(widgetBottom);
    horlayoutWidgetBottom->addWidget(btnClear);
    horlayoutWidgetBottom->addWidget(btnSave);

    //新建侧边栏垂直布局，并将信息栏和记录控制栏添加到其中
    verlayoutWidgetRight=new QVBoxLayout(widgetRight);
    verlayoutWidgetRight->addWidget(widgetDetails);
    verlayoutWidgetRight->addWidget(widgetBottom);

    //新建主界面水平布局，并将日历视图和侧边栏添加到其中
    horLayoutWidget=new QHBoxLayout(this);
    horLayoutWidget->addWidget(calendar,Qt::AlignCenter);
    horLayoutWidget->addWidget(widgetRight);

    //将信号与槽函数连接
    connect(btnBack,SIGNAL(clicked(bool)),this,SLOT(sltBackToToday()));
    connect(calendar, SIGNAL(signalMonthChanged()), this, SLOT(sltMonthChanged()));
    connect(calendar, SIGNAL(signalDayClicked(int)), this, SLOT(sltDayClicked(int)));
    connect(btnClear,SIGNAL(clicked(bool)),this,SLOT(sltClear()));
    connect(btnSave,SIGNAL(clicked(bool)),this,SLOT(sltSave()));

    Q_EMIT calendar->signalMonthChanged();//发射月份切换信号
}

void Widget::initStyle()
{
    QString strStyle="";
    //初始化日期标签样式
    strStyle+=QString("DayLabel{font: 20px; font-family:microsoft yahei;}");
    this->setStyleSheet(strStyle);
}

void Widget::sltDayClicked(int _num)
{
    //设置日期显示标签文字
    labelShowDate->setText(calendar->labelDay[_num]->toString("yyyy-MM-dd"));
    //根据被选择日期是否是节假日设置日期放大显示标签样式
    if(calendar->labelDay[_num]->judgeHoliday())
    {
        labelShowDay->setStyleSheet("background-color:red;color:white;font:64px;font-family:microsoft yahei;");
    }
    else
    {
        labelShowDay->setStyleSheet("background-color: #fb0;color: white; font: 64px;font-family:microsoft yahei;");
    }
    //设置日期放大显示标签文字
    labelShowDay->setText(calendar->labelDay[_num]->toString("d"));
    //显示天干地支年和农历月日
    labelShowLunarYear->setText(calendar->labelDay[_num]->_getLunarYear());
    labelShowLunarMonthAndDay->setText(QString("%1%2").arg(calendar->labelDay[_num]->_getLunarMonth()).arg(calendar->labelDay[_num]->_getLunarDay()));
    //根据被选择日期是否是节假日设置被选择日期的全部节假日显示标签样式及文字
    if(calendar->labelDay[_num]->judgeHoliday())
    {
        labelShowHoliday->setStyleSheet("background-color:red;color:white;font:18px;font-family:microsoft yahei");
        labelShowHoliday->setText(calendar->labelDay[_num]->_getHoliday());
    }
    else
    {
        labelShowHoliday->setStyleSheet("");
        labelShowHoliday->setText("");
    }
    displayText();//设置文本框内容
}

void Widget::sltMonthChanged()
{
    //注释类别上面
    labelShowDate->setText(calendar->toString("yyyy-MM-dd"));
    if(calendar->labelDay[CalendarWidget::selected]->judgeHoliday())
    {
        labelShowDay->setStyleSheet("background-color:red;color:white;font:64px;font-family:microsoft yahei;");
    }
    else
    {
        labelShowDay->setStyleSheet("background-color: #fb0;color: white; font: 64px;font-family:microsoft yahei;");
    }
    if(calendar->labelDay[CalendarWidget::selected]->judgeHoliday())
    {
        labelShowHoliday->setStyleSheet("background-color:red;color:white;font:18px;font-family:microsoft yahei");
        labelShowHoliday->setText(calendar->labelDay[CalendarWidget::selected]->_getHoliday());
    }
    else
    {
        labelShowHoliday->setStyleSheet("");
        labelShowHoliday->setText("");
    }
    labelShowDay->setText(calendar->toString("d"));
    Date tempDate(calendar->year(),calendar->month(),calendar->day());
    QString strLunarMonth = tempDate._getLunarMonth();
    QString strLunarDay =tempDate._getLunarDay();
    labelShowLunarYear->setText(tempDate._getLunarYear());
    labelShowLunarMonthAndDay->setText(QString("%1%2").arg(strLunarMonth).arg(strLunarDay));
    displayText();
}

void Widget::sltBackToToday()
{
    int _year = QDate::currentDate().year();
    int _month = QDate::currentDate().month();
    int _day = QDate::currentDate().day();
    //获取今天年月日
    CalendarWidget::selectedDay=_day;//设置被选择日期
    calendar->jumpToDate(_year, _month, _day);//跳转到今天
}

//void Widget::wheelEvent(QWheelEvent *e)
//{
//    if(e->delta()>0)//如果滚轮滚离使用者
//    {
//        calendar->sltShowPrevMonth();//显示上月
//    }
//    else if(e->delta()<0)//如果滚轮滚向使用者
//    {
//        calendar->sltShowNextMonth();//显示下月
//    }
//}

void Widget::keyPressEvent(QKeyEvent *e)
{
    //获取被选择的日期对应的日期标签数组下标
    int _num=calendar->labelDay[CalendarWidget::selected]->property("num").toInt();
    if(e->key()==Qt::Key_Left)//按下左方向键
    {
        Q_EMIT calendar->labelDay[_num]->signalClicked(_num-1);//发射信号，参数为_num-1
    }
    else if(e->key()==Qt::Key_Right)//按下右方向键
    {
        Q_EMIT calendar->labelDay[_num]->signalClicked(_num+1);//类别上面
    }
    else if(e->key()==Qt::Key_Up)//按下上方向键
    {
        Q_EMIT calendar->labelDay[_num]->signalClicked(_num-7);
    }
    else if(e->key()==Qt::Key_Down)//按下下方向键
    {
        Q_EMIT calendar->labelDay[_num]->signalClicked(_num+7);
    }
}

void Widget::displayText()
{
    //文件路径为/home/Documents/MyNotePad/年年年年月月日日.txt
    QString fileName=dir->path().append('/').append(calendar->labelDay[CalendarWidget::selected]->toString("yyyyMMdd").append(".txt"));
    aFile=new QFile(fileName);
    if(!aFile->exists())//路径不存在
    {
        notepad->clear();//清空文本框
    }
    else//路径存在
    {
        aFile->open(QIODevice::ReadOnly|QIODevice::Text);//以只读方式打开文件
        notepad->setPlainText(aFile->readAll());//设置文本框内容为文件内容
    }
    aFile->close();//关闭文件
}

void Widget::saveText()
{
    //文件路径为/home/Documents/MyNotePad/年年年年月月日日.txt
    aFile=new QFile(dir->path().append('/').append(calendar->labelDay[CalendarWidget::selected]->toString("yyyyMMdd").append(".txt")));
    aFile->open(QIODevice::WriteOnly|QIODevice::Text);//以只写方式打开文件
    QString str=notepad->toPlainText();//获取文本框内容
    if(!str.isEmpty())//文本框内容不为空时
    {
        QByteArray strBytes=str.toUtf8();
        aFile->write(strBytes,strBytes.length());//将文本框内容写入文件
    }
    else
    {
        aFile->remove();//删除文件
    }
    aFile->close();//关闭文件
}

void Widget::sltClear()
{
    notepad->clear();//清除文本框内容
}

void Widget::sltSave()
{
    saveText();//保存文本框内容到文件
}
