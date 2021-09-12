#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <string>

class Message
{
private:
    uint64_t timestamp;
    QString msg;
    QString user;

public:
    Message();
    Message(uint64_t timestamp, QString msg, QString user);
    Message(const Message& old);

    QString getMsg() const;
    QString getUser() const;
    uint64_t getTimestamp() const;
};

#endif // MESSAGE_H
