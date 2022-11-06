#include "server.h"
#include "ui_server.h"
#include <QtNetwork>

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    connect(&tcpServer, &QTcpServer::newConnection, this, &Server::acceptConnection);

}

Server::~Server()
{
    delete ui;
}

void Server::start()
{
    if (!tcpServer.listen(QHostAddress::LocalHost, 6666)) {
        qDebug() << tcpServer.errorString();
        close();
        return;
    }
    ui->startButton->setEnabled(false);
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    ui->serverStatusLabel->setText(tr("监听"));
    ui->serverProgressBar->reset();
}

void Server::acceptConnection()
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection, &QTcpSocket::readyRead, this, &Server::updateServerProgress);
    connect(tcpServerConnection, &QTcpSocket::errorOccurred, this, &Server::displayError);
    ui->serverStatusLabel->setText(tr("接受连接"));
    // 关闭服务器，不再进行监听
    tcpServer.close();
}


void Server::updateServerProgress()
{
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_6_2);

    // 如果接收到的数据小于16个字节，保存到来的文件头结构
    if (bytesReceived <= sizeof(qint64)*2) {
        if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2)
                && (fileNameSize == 0)) {
            // 接收数据总大小信息和文件名大小信息
            in >> totalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64) * 2;
        }
        if((tcpServerConnection->bytesAvailable() >= fileNameSize)
                && (fileNameSize != 0)) {
            // 接收文件名，并建立文件
            in >> fileName;
            ui->serverStatusLabel->setText(tr("接收文件 %1 …")
                                           .arg(fileName));
            bytesReceived += fileNameSize;
            localFile = new QFile(fileName);
            if (!localFile->open(QFile::WriteOnly)) {
                qDebug() << "server: open file error!";
                return;
            }
        } else {
            return;
        }
    }
    // 如果接收的数据小于总数据，那么写入文件
    if (bytesReceived < totalBytes) {
        bytesReceived += tcpServerConnection->bytesAvailable();
        inBlock = tcpServerConnection->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    float temp = (bytesReceived / 1.0) / (totalBytes / 1.0);
    int value = temp * 100;
    ui->serverProgressBar->setMaximum(100);
    ui->serverProgressBar->setValue(value);

    // 接收数据完成时
    if (bytesReceived == totalBytes) {
        tcpServerConnection->close();
        localFile->close();
        ui->startButton->setEnabled(true);
        ui->serverStatusLabel->setText(tr("接收文件 %1 成功！")
                                       .arg(fileName));
    }
}



void Server::displayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << tcpServerConnection->errorString();
    tcpServerConnection->close();
    ui->serverProgressBar->reset();
    ui->serverStatusLabel->setText(tr("服务端就绪"));
    ui->startButton->setEnabled(true);
}

// 开始监听按钮
void Server::on_startButton_clicked()
{
    start();
}
