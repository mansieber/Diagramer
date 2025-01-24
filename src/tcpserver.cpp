#include "tcpserver.h"

#include <QtDebug>

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
    connectionStatus = false;
    qDebug() << "Server initialized";
}

/*
 * Method is called when a client connects to the server.
 *
void TcpServer::incomingConnection(int socketId)
{
    qDebug() << "TcpServer: Client connected, id = " << socketId;
    socket = new ClientConnection(this);
    if ( debugOutput ) {
        debugOutput->appendPlainText("Client connected ...");
    }
    socket->setSocketDescriptor(socketId);
    socket->setDebugOutput(debugOutput);
    connectionStatus = true;
}
*/

/*
 * Method is called to pass a pointer to the debug output text field of the UI.
 */
void TcpServer::setDebugOutput(QPlainTextEdit *output) {
    debugOutput = output;
}

/*
 * Method returns true if the server is connected to the client.
 */
bool TcpServer::isConnected() {
    return connectionStatus;
}

