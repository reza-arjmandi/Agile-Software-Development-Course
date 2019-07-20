#include "Viewer3DDataModel.h"

Viewer3DDataModel::Viewer3DDataModel()
{
    m_DataRoleNames[X] = "X";
    m_DataRoleNames[Y] = "Y";
    m_DataRoleNames[Z] = "Z";
}

int Viewer3DDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_PointClouds.size());
}

QVariant Viewer3DDataModel::data(const QModelIndex &index, int role) const
{
    if(m_PointClouds.empty())
    {
        return QVariant();
    }

    int row = index.row();
    if(row < 0 || row >= m_PointClouds.size())
    {
        return QVariant();
    }

    auto data = m_PointClouds.at(row);

    switch(role) {
    case X:
        return data.X;
    case Y:
        return data.Y;
    case Z:
        return data.Z * -1;
    }
    return QVariant();
}

void Viewer3DDataModel::SetPointClouds(const std::vector<Point> &pointClouds)
{
    m_PointClouds = pointClouds;
    emit endResetModel();
}

QHash<int, QByteArray> Viewer3DDataModel::roleNames() const
{
    return m_DataRoleNames;
}
