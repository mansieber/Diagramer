#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include "commandprocessorinterface.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QString>

#define TCP_PORT 6178

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    ClientConnection(CommandProcessorInterface * cp);
    ~ClientConnection();
    bool isConnected();

private:
    QTcpServer * server;
    QTcpSocket * client;
    CommandProcessorInterface * cmdProc;

private slots:
    void connectionRequest();
    void readClient();
    void clientDisconnected();

signals:
    void newCommand(QString cmd);
};

#endif // CLIENTCONNECTION_H
