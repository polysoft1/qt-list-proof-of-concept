#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include "message.h"

class MyListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(MyRoles)
public:
    MyListModel();
    // Copy constructor needed for Q_DECLARE_METATYPE for QVariant
    MyListModel(const MyListModel &other);

    enum MyRoles {
        UsernameRole = Qt::UserRole + 1,
        MessageRole
    };

    using QAbstractListModel::QAbstractListModel;

    // The way that you need to move data to and from this QML is
    // to have every bit of data be a role.
    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex & parent) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QVariant data(const QModelIndex & index, int role) const override;

private:
    QVector<Message> m_list;
};

Q_DECLARE_METATYPE(MyListModel*)

#endif // MYLISTMODEL_H
