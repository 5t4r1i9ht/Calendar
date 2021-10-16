#include <QObject>
#include <QWidget>
#include <QLabel>
#include "date.h"
#include "daylabel.h"
#ifndef DAYLABEL_CPP
#define DAYLABEL_CPP

DayLabel::DayLabel(QWidget *parent):QLabel(parent),Date(2020,10,01){}//构造函数

//设置日期标签颜色
void DayLabel::setColor()
{
    if(property("type").toString()=="LastMonth"||property("type").toString()=="NextMonth")
    {
        if(!isNotePadExist())
        {
            this->setStyleSheet("background-color:#ffffff;border:1px solid #c3c3c3;color:#999999;");
        }
        else
        {
            this->setStyleSheet("background-color:#ffffff;border:1px solid #66ccff;color:#999999;");
        }
    }
    else if(day()!=CalendarWidget::selectedDay)
    {
        if(!isNotePadExist())
        {
            if(property("type").toString()=="CommonDay")
            {
                this->setStyleSheet("background-color:#ffffff;border:1px solid #c3c3c3;color:#000000;");
            }
            else if(property("type").toString()=="Holiday")
            {
                this->setStyleSheet("background-color:#fff0f0;border:1px solid #c3c3c3;color:#ff0000;");
            }
        }
        else
        {
            if(property("type").toString()=="CommonDay")
            {
                this->setStyleSheet("background-color:#ffffff;border:3px solid #66ccff;color:#000000;");
            }
            else if(property("type").toString()=="Holiday")
            {
                this->setStyleSheet("background-color:#fff0f0;border:3px solid #66ccff;color:#ff0000;");
            }
        }
    }
    else if(day()==CalendarWidget::selectedDay)
    {
        if(property("type").toString()=="CommonDay")
        {
            this->setStyleSheet("background-color:#ffffff;border:3px solid #FFBB00;border-radius:10px;color:#000000;");
        }
        else if(property("type").toString()=="Holiday")
        {
            this->setStyleSheet("background-color:#fff0f0;border:3px solid #FFBB00;border-radius:10px;color:#ff0000;");
        }
    }
    if(property("type").toString()=="CurrentDay")
    {
        this->setStyleSheet(QString("background-color:#FFBB00;color:#000000;"));
    }
}

//显示日期标签对应的日期对应的节日或节气或农历日
void DayLabel::showDay()
{
    QString strText=QString::number(day());
    //?
    QString strLunarFestival="";
    strLunarFestival.append(this->_getLunarFestival());
    QString strSolarHoliday2="";
    strSolarHoliday2.append(this->_getSolarHoliday2());
    QString strSolarHoliday1="";
    strSolarHoliday1.append(this->_getSolarHoliday1());
    QString strSolarTerm="";
    strSolarTerm.append(this->_getSolarTerm());
    QString strLunarDay="";
    strLunarDay.append(this->_getLunarDay());
    if(strLunarDay=="初一")
    {
        strLunarDay.clear();
        strLunarDay.append(this->_getLunarMonth());
    }

    strText.append("\n");
    if(strLunarFestival!="")
    {
        strText.append(strLunarFestival);
    }
    else if(strSolarHoliday2!="")
    {
        strText.append(strSolarHoliday2);
    }
    else if(strSolarHoliday1!="")
    {
        strText.append(strSolarHoliday1);
    }
    else if(strSolarTerm!="")
    {
        strText.append(strSolarTerm);
    }
    else
    {
        strText.append(strLunarDay);
    }

    this->setText(strText);
}

void DayLabel::enterEvent(QEvent*)
{
    if(this->property("type").toString()!="CurrentDay")
    {
        if(property("type").toString()=="LastMonth"||property("type").toString()=="NextMonth")
        {
            this->setStyleSheet("background-color:#ffffff;border:3px solid #FFBB00;border-radius:10px;color:#999999;");
        }
        else if(property("type").toString()=="Holiday")
        {
            this->setStyleSheet("background-color:#fff0f0;border:3px solid #FFBB00;border-radius:10px;color:#ff0000;");
        }
        else if(property("type").toString()=="CommonDay")
        {
            this->setStyleSheet("background-color:#ffffff;border:3px solid #FFBB00;border-radius:10px;color:#000000;");
        }
    }
}

void DayLabel::leaveEvent(QEvent*)
{
    this->setColor();
}

void DayLabel::mousePressEvent(QMouseEvent*)
{
    Q_EMIT signalClicked(this->property("num").toInt());//发射信号
}

bool DayLabel::isNotePadExist()
{
    QString fileName=QDir::homePath().append('/').append("Documents").append('/').append("MyNotepad/").append(this->toString("yyyyMMdd")).append(".txt");
    if(QFile::exists(fileName))
    {
        return true;
    }
    return false;
}

#endif
