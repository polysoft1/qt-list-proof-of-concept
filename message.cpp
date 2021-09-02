#include "message.h"

Message::Message()
    : Message(0, "empty")
{
}
Message::Message(long timestamp, QString msg)
    : timestamp(timestamp), msg(msg)
{
}
Message::Message(const Message& other)
    : timestamp(other.timestamp), msg(other.msg)
{
}

QString Message::getMsg() const {
    return msg;
}
long Message::getTimestamp() const {
    return timestamp;
}
