#include <clock_widget.h>

#include <QPainter>
#include <QTime>
#include <iostream>

Clock::Clock(QWidget* parent)
    : QWidget(parent)
    , _hours(0)
    , _minutes(0)
    , _seconds(0)
{
    setMinimumSize(100,100);
    startTimer(1000);
}

void Clock::timerEvent(QTimerEvent*)
{
    QTime t  = QTime::currentTime();
    _hours   = t.hour();
    _minutes = t.minute();
    _seconds = t.second();

    update();
}


void drawArrow(QPainter& p)
{
    p.drawLine(0,0,  0,10);
}

void Clock::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QPoint center(width()/2, height()/2);
    p.translate(center);

    //circle
    p.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    p.drawEllipse(-153, -153, 300, 300);
    for (int i = 0; i < 360; i+=6)
    {
        p.save();
        p.setPen(Qt::white);
        p.rotate(i);
        if (i % 90 == 0)
        {
            p.scale(3,1);
            p.drawLine(0,-153,0,-130);
        }
        if (i % 5 == 0)
        {
            p.scale(2,1);
            p.drawLine(0,-153,0,-130);
        }
        else
        {
            p.drawLine(0,-153,0,-135);
        }
        p.restore();
    }

    // hoursArrow
    p.save();
    p.rotate( 180 + _hours * 30);
    p.scale(5,5);
    p.setPen(QPen(Qt::white,0.7,Qt::SolidLine,Qt::RoundCap));
    drawArrow(p);
    p.restore();

    // minutesArrow
    p.save();
    p.rotate( 180 + _minutes * 6);
    p.scale(9,9);
    p.setPen(QPen(Qt::white,0.5,Qt::SolidLine,Qt::RoundCap));
    drawArrow(p);
    p.restore();

    // secondsArrow
    p.save();
    p.rotate( 180 + _seconds * 6);
    p.scale(15,15);
    p.setPen(QPen(Qt::blue,0.2,Qt::SolidLine,Qt::RoundCap));
    drawArrow(p);
    p.restore();

    //numbers
    p.setPen(Qt::white);
    QFont mFont("Consolas",15,QFont::Bold);
    p.setFont(mFont);
    p.drawText(-14,-107,"12");
    p.drawText(-7,117,"6");
    p.drawText(100,7,"3");
    p.drawText(-115,7,"9");

    //time
    p.setPen(Qt::black);
    QFont nFont("Consolas",10,QFont::Bold);
    p.setFont(mFont);
    p.drawText(-60, 190,QString::number(_hours) +  ":" + QString::number(_minutes)+ ":" + QString::number(_seconds));
}
