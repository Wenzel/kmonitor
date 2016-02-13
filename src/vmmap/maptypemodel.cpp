#include "maptypemodel.h"

MapTypeModel::MapTypeModel(const std::vector<MMap>& maps, QHash<const MMap*, QString>& hash_map_tag)
    : m_maps(maps),
      m_hash_map_tag(hash_map_tag)
{
    m_header << "Type" << "Size" << "Committed" << "Private" << "Largest";

}

int MapTypeModel::rowCount(const QModelIndex &parent) const
{
    return 4;
}

int MapTypeModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant MapTypeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    /*
    const MapType& map_type = m_list_map_type[index.row()];

    switch (index.column())
    {
    case 0:
        return QString::fromUtf8(map_type.m_type.data(), map_type.m_type.size());
    case 1:
        return map_type.m_size;
    }

    */
    return QVariant();
}

QVariant MapTypeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal and role == Qt::DisplayRole)
        return m_header[section];
    return QVariant();
}
