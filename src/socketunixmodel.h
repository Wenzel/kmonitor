#ifndef SOCKETUNIXMODEL_H
#define SOCKETUNIXMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>

class SocketUNIXModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SocketUNIXModel(QObject *parent = 0);

    void timerEvent(QTimerEvent *event);
    void updateModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    std::vector<struct unix_socket_t> m_unix_socket_list;
    int m_timerId;
    QStringList m_header;
};

#endif // SOCKETUNIXMODEL_H
