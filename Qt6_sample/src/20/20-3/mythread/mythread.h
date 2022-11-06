#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    void stop();
protected:
    void run() override;
private:
    volatile bool stopped;
};


#endif // MYTHREAD_H
