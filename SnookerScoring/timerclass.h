#ifndef TIMERCLASS_H
#define TIMERCLASS_H
#include <QTimer>
#include <QObject>
#include <QDebug>

class TimerClass:public QObject
{
    Q_OBJECT

public:
    TimerClass();
    void settimeCount(int timeCount);
    int gettimeCount();
    void setminuteCount(int timeCount);
    int getminuteCount();
    void resetSeconde();
    void resetMinute();

private slots:
   void secondeSlot();
   void minuteSlot();

signals:
    void secondeCustomSignal(int);
    void minuteCustomSignal(int);

private:
    QTimer *timer;
    QTimer *minute;
    int timeCount;
    int minuteCount;
};

#endif // TIMERCLASS_H
