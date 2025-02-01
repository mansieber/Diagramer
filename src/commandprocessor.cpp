#include "commandprocessor.h"

#include <QDebug>

QRegularExpression const CommandProcessor::cmdStringSep("\\s+");

CommandProcessor::CommandProcessor() {
    mainwindow = new MainWindow();
    mainwindow->show();
    qDebug() << "CommandProcessor: main window opened.";

    initCmdList();

    clientConnect = new ClientConnection();
    qDebug() << "CommandProcessor: client connection created.";

    connect(clientConnect, SIGNAL(newCommand(QString)), this, SLOT(commandTriggered(QString)));
    connect(clientConnect, SIGNAL(newConnectionStatus(QString)), this, SLOT(connectionStatusUpdate(QString)));

    clientConnect->refreshConnectionStatus();
}

CommandProcessor::~CommandProcessor() {
    delete clientConnect;
    qDebug() << "CommandProcessor: client connection deleted.";
}

/*
 * Initialize the list with the commands understood by the tool.
 */
void CommandProcessor::initCmdList() {
    cmdList["create"] = CREATE;
    cmdList["scale"] = SCALE;
    cmdList["plot"] = PLOT;
}

/*
 * Method outputs text in the status line.
 */
void CommandProcessor::connectionStatusUpdate(QString status) {
    mainwindow->setStatusLine(status);
}

/*
 * Method processes a command received via the connection.
 */
void CommandProcessor::commandTriggered(QString cmdString) {
    int cmdId;
    QStringList cmdArgs;

    cmdId = extractCmdId(cmdString, cmdArgs);

    qDebug() << "CommandProcessor: command = " << cmdId;
    qDebug() << "CommandProcessor: " << cmdArgs.size() << " command arguments = " << cmdArgs;
}

/*
 * Method extracts the command from the command string and returns the command id. Arguments are
 * returned via the args argument.
 */
int CommandProcessor::extractCmdId(QString cmdString, QStringList& args) {
    int id;
    QStringList cmdParts;
    QString cmd;
    cmdParts = cmdString.split(cmdStringSep, Qt::SkipEmptyParts);
    if ( cmdParts.size() > 0 ) {
        cmd = cmdParts[0];
        cmdParts.removeFirst();
        args = cmdParts;
        if ( cmdList.contains(cmd) ) {
            id = cmdList.value(cmd);
            qDebug() << "CommandProcessor: command id = " << id;
            return id;
        } else {
            qDebug() << "CommandProcessor: command " << cmd << " not found!";
            return 0;
        }
    } else {
        qDebug() << "CommandProcessor: no command found!";
        return 0;
    }
}



/*
void CommandProcessor::commandTriggered(QString cmd) {
    ui->textEditDebug->appendPlainText(cmd);
}
*/



