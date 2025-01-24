#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtNetwork/QTcpServer>
#include <QPlainTextEdit>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = 0);
    void setDebugOutput(QPlainTextEdit *output);
    bool isConnected();
    void clientDisconnected();

private:
    QPlainTextEdit * debugOutput;
    bool connectionStatus;
//    void incomingConnection(int socketId);
};

#endif // TCPSERVER_H
