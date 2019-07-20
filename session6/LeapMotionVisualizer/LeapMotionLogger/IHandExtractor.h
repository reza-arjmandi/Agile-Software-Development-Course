#ifndef IHANDEXTRACTOR_H
#define IHANDEXTRACTOR_H

#include "HandPosition.h"
#include "Leap.h"

class IHandExtractor
{

public:

    virtual ~IHandExtractor() = default;
    virtual std::vector<HandPosition> ExtractFromFrame(const Leap::Frame& frame) = 0;

};

#endif // IHANDEXTRACTOR_H
