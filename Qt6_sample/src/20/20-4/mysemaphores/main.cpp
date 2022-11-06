#include <QtCore>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

const int DataSize = 10;
const int BufferSize = 5;
char buffer[BufferSize];
QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;

// 生产者
class Producer : public QThread
{
public:
    void run() override;
};

void Producer::run()
{
    for (int i = 0; i < DataSize; ++i) {
        freeBytes.acquire();
        buffer[i % BufferSize] = "ACGT"[QRandomGenerator::global()->bounded(4)];
        qDebug() << QString("producer: %1").arg(buffer[i % BufferSize]);
        usedBytes.release();
    }
}

// 消费者
class Consumer : public QThread
{
public:
    void run() override;
};

void Consumer::run()
{
    for (int i = 0; i < DataSize; ++i) {
        usedBytes.acquire();
        qDebug() << QString("consumer: %1").arg(buffer[i % BufferSize]);
        freeBytes.release();
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();
    producer.wait();
    consumer.wait();
    return app.exec();
}
