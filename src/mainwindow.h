#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setStatusLine(QString);

private:
    Ui::MainWindow * ui;

private slots:
    void clearDebugOutput();

};

#endif // MAINWINDOW_H
