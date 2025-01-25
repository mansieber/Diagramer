#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "commandprocessorinterface.h"
#include "clientconnection.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, CommandProcessorInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void virtual setStatus(QString status);
    void virtual processCommand(QString cmd);

private:
    Ui::MainWindow *ui;
    ClientConnection * clientConnect;

private slots:
    void clearDebugOutput();

public slots:
//    void virtual commandTriggered(QString cmd);

};

#endif // MAINWINDOW_H
