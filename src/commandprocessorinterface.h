#ifndef COMMANDPROCESSORINTERFACE_H
#define COMMANDPROCESSORINTERFACE_H

#include <QString>

class CommandProcessorInterface
{
public:
//    CommandProcessorInterface() {};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

    void virtual setStatus(QString) {};
    void virtual processCommand(QString) {};

#pragma GCC diagnostic pop

//    void virtual commandTriggered(QString cmd);
};

#endif // COMMANDPROCESSORINTERFACE_H
