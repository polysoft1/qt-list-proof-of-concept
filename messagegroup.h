#ifndef MessageGroup_H
#define MessageGroup_H

#include <QString>
#include <QObject>
#include "MessageModel.h"

class MessageGroup
{
private:
    QString user_ = "User Name";
    bool isSelf = false;
    MessageModel * model;

public:
    MessageGroup();
    MessageGroup(const MessageGroup& old);
    MessageGroup(QString user, MessageModel * model, bool self);

    QString getUser() const;
    bool getSelf() const;
    MessageModel * getModel() const;
};

#endif // MessageGroup_H
