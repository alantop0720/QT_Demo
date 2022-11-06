#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStringEncoder>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myProcess = new QProcess(this);
    connect(myProcess, &QProcess::readyRead, this, &MainWindow::showResult);
    connect(myProcess, &QProcess::stateChanged, this, &MainWindow::showState);
    connect(myProcess, &QProcess::errorOccurred, this, &MainWindow::showError);
    connect(myProcess, &QProcess::finished, this, &MainWindow::showFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString program = "cmd.exe";
    QStringList arguments;
    arguments << "/c dir&pause";
    myProcess->start(program, arguments);
}


void MainWindow::showResult()
{
    QByteArray encodedString = myProcess->readAll();
    auto toUtf16 = QStringDecoder(QStringDecoder::System);
    QString string = toUtf16(encodedString);
    qDebug() << "showResult: " << Qt::endl << string;
}

void MainWindow::showState(QProcess::ProcessState state)
{
    qDebug() << "showState: ";
    if (state == QProcess::NotRunning) {
        qDebug() << "Not Running";
    } else if (state == QProcess::Starting) {
        qDebug() << "Starting";
    }  else {
        qDebug() << "Running";
    }
}

void MainWindow::showError()
{
    qDebug() << "showError: " << Qt::endl << myProcess->errorString();
}


void MainWindow::showFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "showFinished: " << Qt::endl << exitCode << exitStatus;
}
