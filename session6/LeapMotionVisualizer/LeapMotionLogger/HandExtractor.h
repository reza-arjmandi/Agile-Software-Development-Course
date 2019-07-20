#ifndef HANDEXTRACTOR_H
#define HANDEXTRACTOR_H

#include "IHandExtractor.h"

class HandExtractor : public IHandExtractor
{

public:

    std::vector<HandPosition> ExtractFromFrame(const Leap::Frame &frame);

};

#endif // HANDEXTRACTOR_H
