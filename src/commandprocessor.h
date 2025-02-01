#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "mainwindow.h"
#include "clientconnection.h"

#include <QObject>
#include <QMap>
#include <QRegularExpression>
#include <QString>
#include <QStringList>

enum comIDs {
    CREATE = 1, SCALE, PLOT
};

class CommandProcessor : public QObject
{
    Q_OBJECT
public:
    CommandProcessor();
    ~CommandProcessor();

private:
    MainWindow * mainwindow;
    ClientConnection * clientConnect;
    QMap<QString, int> cmdList;
    static const QRegularExpression cmdStringSep;
    void initCmdList();
    int extractCmdId(QString, QStringList&);

public slots:
    void commandTriggered(QString);
    void connectionStatusUpdate(QString);

};

#endif // COMMANDPROCESSOR_H
