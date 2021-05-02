#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QObject>

class Message : public QObject
{
public:
    Message();
    Message(const Message& old);
    Message(QString user, QString msg);
    QString user_ = "User Name";
    QString msg_ = "Message here";

    QString getUser() const;
    QString getMsg() const;
};

#endif // MESSAGE_H
