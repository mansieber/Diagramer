#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDataStream>
#include <QByteArray>
#include <QString>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    tcpServer = new TcpServer(this);
    ui->setupUi(this);

    connect(ui->buttonClearDebug, SIGNAL(clicked()), this, SLOT(clearDebugOutput()));

    if ( ! tcpServer->listen(QHostAddress::Any, TCP_PORT) ) {
        ui->statusBar->showMessage("Failed to bind to tcp port " + QString::number(TCP_PORT) + "!");
    } else {
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connectionRequest()));
        ui->statusBar->showMessage("Listening for connections to port "+ QString::number(TCP_PORT));
        tcpServer->setDebugOutput(ui->textEditDebug);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Method empties the debug output.
 */
void MainWindow::clearDebugOutput() {
    ui->textEditDebug->setPlainText("");
}

/*
 * Method stores and activates the client connection.
 */
void MainWindow::connectionRequest() {
    tcpClient = tcpServer->nextPendingConnection();
    qDebug() << "Connection requested ...";
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(tcpClient, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    ui->statusBar->showMessage("Client connected");
    qDebug() << "Connection established";
}

/*
 * Method reads data from the socket. Function is called when data is available.
 */
void MainWindow::readClient()
{
    QByteArray bytes = tcpClient->readAll();
    QString cmdString = QString::fromStdString(bytes.toStdString());
    ui->textEditDebug->appendPlainText(cmdString);
    qDebug() << bytes.size() << " bytes read: " << cmdString;
}

/*
 * Method disconnects the client.
 */
void MainWindow::clientDisconnected() {
    tcpClient->deleteLater();
    ui->statusBar->showMessage("Client disconnected ... Listening for connections");
}

