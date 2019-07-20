#ifndef LEAPMOTIONDATAACQUISITOR_H
#define LEAPMOTIONDATAACQUISITOR_H

#include <QObject>
#include <memory>


#include "Leap.h"
#include "ILeapMotionDataAcquisitor.h"
#include "IHandExtractor.h"

class LeapMotionDataAcquisitor : public QObject, Leap::Listener, public ILeapMotionDataAcquisitor
{

    Q_OBJECT

public:

    LeapMotionDataAcquisitor(std::unique_ptr<IHandExtractor> handExtractor);

    Q_INVOKABLE void Run();
    Q_INVOKABLE void Stop();

private:

    void onFrame(const Leap::Controller& controller) override;
    std::vector<Point> ExtractPointClouds(const std::vector<HandPosition>& handPositions) const;

    Leap::Controller m_Controller;
    std::unique_ptr<IHandExtractor> m_HandExtractor;

};

#endif // LEAPMOTIONDATAACQUISITOR_H
