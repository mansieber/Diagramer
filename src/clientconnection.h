#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QString>

#define TCP_PORT 6178

enum ConnectStatus {
    NO_BINDING, CLIENT_CONNECTED, NO_CLIENT_CONNECTED
};

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    ClientConnection();
    ~ClientConnection();
    void refreshConnectionStatus();

private:
    QTcpServer * server;
    QTcpSocket * client;
    ConnectStatus connectStatus = NO_BINDING;

private slots:
    void connectionRequest();
    void readClient();
    void clientDisconnected();

signals:
    void newCommand(QString cmdString);
    void newConnectionStatus(QString status);
};

#endif // CLIENTCONNECTION_H
