#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QObject>

class Message : public QObject
{
public:
    Message();
    Message(const Message& old);
    Message(QString user, QString msg, bool self);
    QString user_ = "User Name";
    QString msg_ = "Message here";
    bool isSelf = false;

    QString getUser() const;
    QString getMsg() const;
    bool getSelf() const;
};

#endif // MESSAGE_H
