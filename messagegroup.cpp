#include "messagegroup.h"

MessageGroup::MessageGroup(QString user, MessageModel * model, bool self)
    : user_(user), isSelf(self), model(model)
{

}

MessageGroup::MessageGroup()
    : MessageGroup("default user", new MessageModel, false)
{

}

MessageGroup::MessageGroup(const MessageGroup& old) {
    this->user_ = old.user_;
    this->model = old.model;
    this->isSelf = old.isSelf;
}


QString MessageGroup::getUser() const {
    return user_;
}
MessageModel * MessageGroup::getModel() const {
    return model;
}
bool MessageGroup::getSelf() const {
    return isSelf;
}

