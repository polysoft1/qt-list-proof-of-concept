#include "messagegroupmodel.h"

#include <QDebug>
#include <stdlib.h>

MessageGroupModel::MessageGroupModel(QString selfUser, uint64_t maxCombineDiff)
    : selfUser(selfUser), maxCombineDiff(maxCombineDiff)
{
}


void MessageGroupModel::addMessage(Message newMsg) {
    // Plan:
    // - Iterate from bottom to top of the groups
    //   until a message is found with a timestamp
    //   less (earlier) than the new message.
    // - If first message, create a new group.
    // - If between two groups, check to see which
    //   group has the same user. If neither, create
    //   a new group between them. If the earlier
    //   group, add to the end of the last group.
    //   If the later group, add to the beginning.
    // - If in middle of a group, check user. If
    //   the user is the same, add to that group.
    //   If the user is different, split the group,
    //   and call the code for when it's between
    //   two groups to create a new group.
    for (int groupIndex = groupList.length() - 1; groupIndex >= 0; groupIndex--) {
        auto msgGroup = groupList.at(groupIndex);
        QVector<Message>& msgList = msgGroup.getModel()->msgList;
        QString newUser = newMsg.getUser();

        for (int msgIndex = msgList.length() - 1; msgIndex >= 0; msgIndex--) {
            auto msg = msgList.at(msgIndex);
            uint64_t timeDiff = newMsg.getTimestamp() - msg.getTimestamp();
            if (timeDiff >= 0) {
                // Place after this message

                if (msgGroup.getUser() == newUser && timeDiff <= maxCombineDiff) {
                    // Add to existing group
                    msgList.insert(msgIndex + 1, newMsg);
                } else {
                    // New or beginning of next group.

                    if (msgIndex == msgList.length() - 1) {
                        // Can insert to a group after this one
                        // Check to see if it can be added to the next group.
                        // If not, create a new one.
                        if (groupIndex + 1 < groupList.length() && groupList.at(groupIndex + 1).getUser() == newUser && timeDiff <= maxCombineDiff) {
                            groupList.at(groupIndex + 1).getModel()->msgList.insert(0, newMsg);
                        } else {
                            MessageModel * model = new MessageModel;
                            model->msgList.append(newMsg);
                            groupList.insert(groupIndex + 1, MessageGroup{ newMsg.getUser(), model, newMsg.getUser() == selfUser });
                        }
                    } else {
                        // Split the group

                        // Add the new group for the new message
                        MessageModel * newMsgModel = new MessageModel;
                        newMsgModel->msgList.append(newMsg);
                        groupList.insert(groupIndex + 1, MessageGroup{ newMsg.getUser(), newMsgModel, newMsg.getUser() == selfUser });

                        // Add the new group for the remaining messages from the split group
                        MessageModel * remainingMsgsModel = new MessageModel;
                        // Add all from end to but NOT including the one at msgIndex
                        for (int i = msgList.length() - 1; i > msgIndex; i--) {
                            remainingMsgsModel->msgList.append(msgList.takeAt(i));
                        }
                        groupList.insert(groupIndex + 2, MessageGroup{ msgGroup.getUser(), remainingMsgsModel, msgGroup.getUser() == selfUser });
                    }
                }
                return;
            }
        }
    }
    // Reached the end. Add to beginning of timeline
    // Check if the first group has the same user.
    if (!groupList.isEmpty() && groupList.first().getUser() == newMsg.getUser()) {
        groupList.first().getModel()->msgList.insert(0, newMsg);
    } else {
        MessageModel * newMsgModel = new MessageModel;
        newMsgModel->msgList.append(newMsg);
        groupList.insert(0, MessageGroup{ newMsg.getUser(), newMsgModel, newMsg.getUser() == selfUser });
    }
}

// Copy constructor needed for Q_DECLARE_METATYPE for QVariant
MessageGroupModel::MessageGroupModel(const MessageGroupModel &other) {
    this->groupList = other.groupList;
}

// The way that you need to move data to and from this QML is
// to have every bit of data be a role.
QHash<int, QByteArray> MessageGroupModel::roleNames() const {
    QHash<int, QByteArray> hash;
    hash[UsernameRole] = "user";
    hash[MessagesModelRole] = "msg_model";
    hash[SelfRole] = "self";
    return hash;
}

int MessageGroupModel::rowCount(const QModelIndex & parent = QModelIndex()) const {
    if (parent.isValid())
        return 0;
    return groupList.size();
}

bool MessageGroupModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;

    /*Message &item = m_list[index.row()];
    if (role == UsernameRole)
        item.user = value.toString();
    else if (role == MessageRole)
        item.msg = value.toString();
    else
        return false;*/

    emit dataChanged(index, index, { role } );

    return true ;

}

QVariant MessageGroupModel::data(const QModelIndex & index, int role = Qt::DisplayRole) const {
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const MessageGroup &item = groupList.at(index.row());
    if (role == UsernameRole) return item.getUser();
    if (role == MessagesModelRole) {
        return QVariant::fromValue(item.getModel());
    }
    if (role == SelfRole) return item.getSelf();

    qDebug() << "Unknown role in group data " << roleNames()[role];

    return {};
}
