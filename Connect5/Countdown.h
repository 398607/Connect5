#ifndef COUND_H
#define COUND_H

#include<QTimer>

class Countdown : public QObject
{
    Q_OBJECT
    
public:
    Countdown(int max) {
        maxV = max;
        v = max;
        on = false;
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Countdown::oneSec);
        timer->start(1000);
        emit timeChanged(v);
    }
signals:
    void timeChanged(int time);
    void timeOut();
    void oneSecSignal();
public slots:
    void oneSec() {
        if (on) {
            v--;
            emit oneSecSignal();
            emit timeChanged(v);
            if (v == 0) {
                v = maxV;
                emit timeChanged(maxV);
                emit timeOut();
            }
        }
    }
    void pause() {
        on = false;
    }
    void stop() {
        on = false;
        v = maxV;
        emit timeChanged(v);
    }
    void resume() {
        on = true;
    }
    void start() {
        v = maxV;
        emit timeChanged(maxV);
        on = true;
    }
private:
    int v;
    int maxV;
    bool on;
};

#endif
