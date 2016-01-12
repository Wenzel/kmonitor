#include "sysinfo.h"
#include "socketunixmodel.h"

SocketUNIXModel::SocketUNIXModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_header << "Num" << "RefCount" << "Protocol" << "Flags" << "Type" << "State" << "Inode" << "Path";
    m_timerId = startTimer(1000);
    updateModel();
}

void SocketUNIXModel::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    updateModel();
}

void SocketUNIXModel::updateModel()
{
    beginResetModel();

    m_unix_socket_list = getSocketUNIX();

    endResetModel();
}

int SocketUNIXModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_unix_socket_list.size();
}

int SocketUNIXModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 8;
}

QVariant SocketUNIXModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_unix_socket_list.size())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    const struct unix_socket_t &unix_socket = m_unix_socket_list[index.row()];

    switch (index.column())
    {
    case 0:
        return QString::fromUtf8(unix_socket.num.data(), unix_socket.num.size());
    case 1:
        return unix_socket.ref_count;
    case 2:
        return unix_socket.protocol;
    case 3:
        return unix_socket.flags;
    case 4:
        return unix_socket.type;
    case 5:
        return unix_socket.state;
    case 6:
        return unix_socket.inode;
    case 7:
        return QString::fromUtf8(unix_socket.path.data(), unix_socket.path.size());
    }

    return QVariant();
}

QVariant SocketUNIXModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal and role == Qt::DisplayRole)
        return m_header[section];
    return QVariant();
}
