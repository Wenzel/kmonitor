#ifndef MAPTYPEMODEL_H
#define MAPTYPEMODEL_H

#include <QAbstractListModel>
#include <QHash>

#include "processinfo.h"

class MapTypeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    MapTypeModel(const std::vector<MMap>& maps, QHash<const MMap*, QString>& hash_map_tag);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    const std::vector<MMap>& m_maps;
    QHash<const MMap*, QString>& m_hash_map_tag;
    QStringList m_header;
};

#endif // MAPTYPEMODEL_H
