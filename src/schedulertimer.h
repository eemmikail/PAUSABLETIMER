#ifndef SCHEDULERTIMER_H
#define SCHEDULERTIMER_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QDebug>

class SchedulerTimer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SchedulerTimer::ScheduleState state READ currentState NOTIFY currentStateChanged)
    Q_PROPERTY(int elapsedMS READ getElapsedMS WRITE setElapsedMS NOTIFY elapsedMSChanged)
    Q_PROPERTY(int remainingMS READ getRemainingMS WRITE setRemainingMS NOTIFY remainingMSChanged)
    Q_PROPERTY(int targetMS READ getTargetMS WRITE setTargetMS NOTIFY targetMSChanged)

public:
    explicit SchedulerTimer(QObject *parent = nullptr);
    ~SchedulerTimer() {
        delete counterTimer;
        counterTimer = NULL;
    }

    enum ScheduleState {
        RUNNING,
        PAUSED,
        STOPPED
    };

    Q_ENUM(ScheduleState);

    ScheduleState currentState() const;
    const QTime &getTargetTime() const;
    int getElapsedMS() const;
    void setElapsedMS(int newElapsedMS);

    int getRemainingMS() const;
    void setRemainingMS(int newRemainingMS);

    int getTargetMS() const;
    void setTargetMS(int newTargetMS);

signals:
    void currentStateChanged(SchedulerTimer::ScheduleState);
    void elapsedMSChanged();

    void remainingMSChanged();

    void targetMSChanged();

public slots:
    void start();
    void stop();
    void pause();
    void resume();

    void setTargetTime(const QTime &newTargetTime);
    void setTargetTime(const QString targetTimeMSString);
private:
    SchedulerTimer::ScheduleState m_currentState;
    QTime targetTime = QTime(0,0,0,0);
    QTime elapsedTime = QTime(0,0,0,0);
    QTimer *counterTimer;

    int elapsedMS;
    int remainingMS;
    int targetMS;

private slots:
    void onCounterTimerTimeout();
    void setCurrentState(SchedulerTimer::ScheduleState newCurrentState);

    void reset();
};

#endif // SCHEDULERTIMER_H
