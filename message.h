#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>


class Message
{
private:
    long timestamp;
    QString msg;

public:
    Message();
    Message(long timestamp, QString msg);
    Message(const Message& old);

    QString getMsg() const;
    long getTimestamp() const;
};

#endif // MESSAGE_H
