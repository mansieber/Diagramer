#include "clientconnection.h"

#include <QObject>
#include <QByteArray>
#include <QDebug>

ClientConnection::ClientConnection(CommandProcessorInterface * cp) {
    cmdProc = cp;
    server = new QTcpServer();
    qDebug() << "Server instantiated";

    if ( ! server->listen(QHostAddress::Any, TCP_PORT) ) {
        cmdProc->setStatus("Failed to bind to tcp port " + QString::number(TCP_PORT) + "!");
    } else {
        connect(server, SIGNAL(newConnection()), this, SLOT(connectionRequest()));
        cmdProc->setStatus("Listening for connections to port " + QString::number(TCP_PORT));
    }

//    connect(this, SIGNAL(newCommand(QString)), ( const QObject * ) ui, SLOT(commandTriggered(QString)));
}

ClientConnection::~ClientConnection() {
    client->deleteLater();
    if ( server ) delete server;
}

/*
 * Method stores and activates the client connection.
 */
void ClientConnection::connectionRequest() {
    client = server->nextPendingConnection();
    qDebug() << "Connection requested ...";
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    cmdProc->setStatus("Client connected");
    qDebug() << "Connection established";
}

/*
 * Method reads data from the socket. Function is called when data is available.
 */
void ClientConnection::readClient()
{
    QByteArray bytes = client->readAll();
    QString cmdString = QString::fromStdString(bytes.toStdString());
    qDebug() << bytes.size() << " bytes read: " << cmdString;
//    emit newCommand(cmdString);
    cmdProc->processCommand(cmdString);
}

/*
 * Method disconnects the client.
 */
void ClientConnection::clientDisconnected() {
    client->deleteLater();
    cmdProc->setStatus("Client disconnected ... Listening for connections");
    qDebug() << "Client disconnected";
}


