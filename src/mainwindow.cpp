#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonClearDebug, SIGNAL(clicked()), this, SLOT(clearDebugOutput()));
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "MainWindow: ui deleted";
}

/*
 * Method outputs text in the status line.
 */
void MainWindow::setStatusLine(QString status) {
    ui->statusBar->showMessage(status);
}

/*
 * Method empties the debug output.
 */
void MainWindow::clearDebugOutput() {
    ui->textEditDebug->setPlainText("");
}
