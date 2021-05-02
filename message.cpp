#include "message.h"

Message::Message(QString user, QString msg)
    : user_(user), msg_(msg)
{

}

Message::Message()
    : Message("default user", "default msg")
{

}

Message::Message(const Message& old) {
    this->user_ = old.user_;
    this->msg_ = old.msg_;
}


QString Message::getUser() const {
    return user_;
}
QString Message::getMsg() const {
    return msg_;
}
