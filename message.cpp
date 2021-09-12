#include "message.h"

Message::Message()
    : Message(0, "empty", "user")
{
}
Message::Message(uint64_t timestamp, QString msg, QString user)
    : timestamp(timestamp), msg(msg), user(user)
{
}
Message::Message(const Message& other)
    : timestamp(other.timestamp), msg(other.msg), user(other.user)
{
}

QString Message::getMsg() const {
    return msg;
}
QString Message::getUser() const {
    return user;
}
uint64_t Message::getTimestamp() const {
    return timestamp;
}
