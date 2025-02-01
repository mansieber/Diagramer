#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "mainwindow.h"
#include "clientconnection.h"

#include <QMap>
#include <QRegularExpression>
#include <QString>
#include <QStringList>

enum comIDs {
    CREATE = 1, SCALE, PLOT
};

class CommandProcessor : CommandProcessorInterface
{
public:
    CommandProcessor();
    ~CommandProcessor();
    void virtual setStatus(QString);
    void virtual processCommand(QString);

private:
    MainWindow * mainwindow;
    ClientConnection * clientConnect;
    QMap<QString, int> cmdList;
    static const QRegularExpression cmdStringSep;
    void initCmdList();
    int extractCmdId(QString, QStringList&);

public slots:
    //    void virtual commandTriggered(QString cmd);

};

#endif // COMMANDPROCESSOR_H
