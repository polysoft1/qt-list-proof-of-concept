#include "message.h"

Message::Message(QString user, QString msg, bool self)
    : user_(user), msg_(msg), isSelf(self)
{

}

Message::Message()
    : Message("default user", "default msg", false)
{

}

Message::Message(const Message& old) {
    this->user_ = old.user_;
    this->msg_ = old.msg_;
    this->isSelf = old.isSelf;
}


QString Message::getUser() const {
    return user_;
}
QString Message::getMsg() const {
    return msg_;
}
bool Message::getSelf() const {
    return isSelf;
}

