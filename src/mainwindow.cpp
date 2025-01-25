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
    ui->setupUi(this);
    clientConnect = new ClientConnection(this);

    connect(ui->buttonClearDebug, SIGNAL(clicked()), this, SLOT(clearDebugOutput()));
}

MainWindow::~MainWindow()
{
    delete clientConnect;
    delete ui;
}

/*
 * Method outputs text in the status line.
 */
void MainWindow::setStatus(QString s) {
    ui->statusBar->showMessage(s);
}

/*
 * Method empties the debug output.
 */
void MainWindow::clearDebugOutput() {
    ui->textEditDebug->setPlainText("");
}

/*
void MainWindow::commandTriggered(QString cmd) {
    ui->textEditDebug->appendPlainText(cmd);
}
*/

void MainWindow::processCommand(QString cmd) {
    ui->textEditDebug->appendPlainText(cmd);
}
