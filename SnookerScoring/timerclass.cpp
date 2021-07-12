#include "timerclass.h"

TimerClass::TimerClass()
{
timer = new QTimer;
minute = new QTimer;
timer->start(1000);
minute->start(1000);
connect(timer,SIGNAL(timeout()),this,SLOT(secondeSlot()));
connect(minute,SIGNAL(timeout()),this,SLOT(minuteSlot()));
timeCount = 1;
minuteCount = 0;
}

void TimerClass::settimeCount(int t) {
    this->timeCount = t;
}
int TimerClass::gettimeCount() {
    return timeCount;
}
void TimerClass::setminuteCount(int t){
    this->minuteCount = t;
}
int TimerClass::getminuteCount(){
    return minuteCount;
}


void TimerClass::resetSeconde()
{
 timeCount=1;
}
void TimerClass::resetMinute()
{
  minuteCount=1;
}

void TimerClass::secondeSlot()
{
   qDebug()<< minuteCount <<":"<< timeCount;

   emit secondeCustomSignal(timeCount);

       timeCount++;
       if(timeCount == 60) {
           timeCount=0;
           minuteCount++;
       }
}

void TimerClass::minuteSlot()
{

    emit minuteCustomSignal(minuteCount);
    //minuteCount++;
}
