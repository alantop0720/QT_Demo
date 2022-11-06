#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    ui->progressBar->hide();
    ui->lineEdit->setText("https://mirrors.sjtug.sjtu.edu.cn/qt/archive/online_installers/4.3/qt-unified-windows-x86-4.3.0-1-online.exe");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::readyRead, this, &MainWindow::httpReadyRead);
    connect(reply, &QNetworkReply::downloadProgress,
            this, &MainWindow::updateDataReadProgress);
    connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);
}

void MainWindow::httpReadyRead()
{
    if (file) file->write(reply->readAll());
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

void MainWindow::httpFinished()
{
    ui->progressBar->hide();
    if(file) {
        file->close();
        delete file;
        file = 0;
    }
    reply->deleteLater();
    reply = 0;
    QMessageBox::information(this, tr("提示"), tr("下载完成！"), QMessageBox::Ok);
}

// 下载按钮
void MainWindow::on_pushButton_clicked()
{
    url = ui->lineEdit->text();
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    if (fileName.isEmpty()) fileName = "index.html";
    file = new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly))
    {
        delete file;
        file = 0;
        return;
    }
    startRequest(url);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
}

