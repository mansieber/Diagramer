#include "clientconnection.h"

#include <QObject>
#include <QByteArray>
#include <QDebug>

ClientConnection::ClientConnection() {
    server = new QTcpServer();
    qDebug() << "ClientConnection: server instantiated.";

    if ( ! server->listen(QHostAddress::Any, TCP_PORT) ) {
        connectStatus = NO_BINDING;
    } else {
        connect(server, SIGNAL(newConnection()), this, SLOT(connectionRequest()));
        connectStatus = NO_CLIENT_CONNECTED;
    }
}

ClientConnection::~ClientConnection() {
    client->deleteLater();
    if ( server ) delete server;
    qDebug() << "ClientConnection: client/server deleted.";
}

/*
 * Method stores and activates the client connection.
 */
void ClientConnection::connectionRequest() {
    client = server->nextPendingConnection();
    qDebug() << "Connection requested ...";
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connectStatus = CLIENT_CONNECTED;
    emit newConnectionStatus("Client connected");
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
    emit newCommand(cmdString);
}

/*
 * Method disconnects the client.
 */
void ClientConnection::clientDisconnected() {
    client->deleteLater();
    connectStatus = NO_CLIENT_CONNECTED;
    emit newConnectionStatus("Client disconnected ... Listening for connections");
    qDebug() << "Client disconnected";
}

/*
 * Method updates the connection status.
 */
void ClientConnection::refreshConnectionStatus() {
    switch ( connectStatus ) {
    case NO_BINDING:
        emit newConnectionStatus("Failed to bind to tcp port " + QString::number(TCP_PORT) + "!");
        break;
    case NO_CLIENT_CONNECTED:
        emit newConnectionStatus("Listening for connections to port " + QString::number(TCP_PORT));
        break;
    case CLIENT_CONNECTED:
        emit newConnectionStatus("Client connected");
        break;
    }

}
