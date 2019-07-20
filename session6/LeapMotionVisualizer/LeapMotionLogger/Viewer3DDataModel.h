#ifndef LEAPMOTIONDATAMODEL_H
#define LEAPMOTIONDATAMODEL_H

#include <QAbstractListModel>
#include "ILeapMotionDataAcquisitor.h"
#include "I3DViewUpdater.h"

class Viewer3DDataModel: public QAbstractListModel, public I3DViewUpdater
{
     Q_OBJECT

public:
    Viewer3DDataModel();

    enum DataRoleNames{
        X = Qt::UserRole,
        Y = Qt::UserRole + 2,
        Z = Qt::UserRole + 4
    };

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    void SetPointClouds(const std::vector<Point>& pointClouds) override;

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QHash<int, QByteArray> m_DataRoleNames;
    std::vector<Point> m_PointClouds;

};

#endif // LEAPMOTIONDATAMODEL_H
