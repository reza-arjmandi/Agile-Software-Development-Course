#ifndef I3DVIEWUPDATER_H
#define I3DVIEWUPDATER_H

#include <vector>
#include "Point.h"

class I3DViewUpdater
{

public:

    virtual ~I3DViewUpdater() = default;
    virtual void SetPointClouds(const std::vector<Point>& pointClouds) = 0;

};

#endif // I3DVIEWUPDATER_H
