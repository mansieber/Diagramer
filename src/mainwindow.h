#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcpserver.h"

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>

#define TCP_PORT 6178

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TcpServer * tcpServer;
    QTcpSocket * tcpClient;

private slots:
    void clearDebugOutput();
    void connectionRequest();
    void readClient();
    void clientDisconnected();
};

#endif // MAINWINDOW_H
