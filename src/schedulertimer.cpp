#include "schedulertimer.h"

SchedulerTimer::SchedulerTimer(QObject *parent)
    : QObject{parent}
    , m_currentState(ScheduleState::STOPPED)
    , counterTimer(new QTimer(parent))
    , elapsedMS(0)
    , remainingMS(0)
    , targetMS(0)
{
    counterTimer->setInterval(100);
    connect(counterTimer,&QTimer::timeout,this,&SchedulerTimer::onCounterTimerTimeout);
    setTargetTime("10000");
}

SchedulerTimer::ScheduleState SchedulerTimer::currentState() const
{
    return m_currentState;
}

void SchedulerTimer::setCurrentState(SchedulerTimer::ScheduleState newCurrentState)
{
    m_currentState = newCurrentState;
    emit currentStateChanged(m_currentState);
}

const QTime &SchedulerTimer::getTargetTime() const
{
    return targetTime;
}

void SchedulerTimer::setTargetTime(const QTime &newTargetTime)
{
    targetTime = newTargetTime;
}

void SchedulerTimer::setTargetTime(const QString targetTimeMSString) {
    int ms = targetTimeMSString.toInt();
    setTargetMS(ms);
    targetTime = QTime(0,0,0,0);
    targetTime = targetTime.addMSecs(ms);
}

int SchedulerTimer::getTargetMS() const
{
    return targetMS;
}

void SchedulerTimer::setTargetMS(int newTargetMS)
{
    if (targetMS == newTargetMS)
        return;
    targetMS = newTargetMS;
    emit targetMSChanged();
}

int SchedulerTimer::getRemainingMS() const
{
    return remainingMS;
}

void SchedulerTimer::setRemainingMS(int newRemainingMS)
{
    if (remainingMS == newRemainingMS)
        return;
    remainingMS = newRemainingMS;
    emit remainingMSChanged();
}

int SchedulerTimer::getElapsedMS() const
{
    return elapsedMS;
}

void SchedulerTimer::setElapsedMS(int newElapsedMS)
{
    if (elapsedMS == newElapsedMS)
        return;
    elapsedMS = newElapsedMS;
    emit elapsedMSChanged();
}

void SchedulerTimer::start()
{
    if(m_currentState == SchedulerTimer::RUNNING)
        return;

    reset();

    setCurrentState(SchedulerTimer::RUNNING);
    counterTimer->start();
}

void SchedulerTimer::stop()
{
    if(m_currentState == SchedulerTimer::STOPPED)
        return;

    setCurrentState(SchedulerTimer::STOPPED);
    counterTimer->stop();
    elapsedTime = QTime(0,0,0,0);
}

void SchedulerTimer::pause()
{
    if(m_currentState == SchedulerTimer::PAUSED)
        return;

    setCurrentState(SchedulerTimer::PAUSED);
    counterTimer->stop();
}

void SchedulerTimer::resume() {
    if(m_currentState == SchedulerTimer::RUNNING)
        return;

    setCurrentState(SchedulerTimer::RUNNING);
    counterTimer->start();
}

void SchedulerTimer::reset() {
    elapsedTime = QTime(0,0,0,0);
    setElapsedMS(0);
    setRemainingMS(targetMS);
}

void SchedulerTimer::onCounterTimerTimeout()
{
    elapsedTime = elapsedTime.addMSecs(100);

    int rmnMS =  elapsedTime.msecsTo(targetTime);

    setRemainingMS(rmnMS);
    setElapsedMS(targetMS - remainingMS);

    if(rmnMS <= 0) {
        stop();
    }

    qDebug() << elapsedMS << remainingMS;
}
