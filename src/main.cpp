#include "commandprocessor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CommandProcessor cp;

    return a.exec();
}
