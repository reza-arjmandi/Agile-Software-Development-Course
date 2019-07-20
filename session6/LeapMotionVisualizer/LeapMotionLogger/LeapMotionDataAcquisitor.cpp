#include "LeapMotionDataAcquisitor.h"

LeapMotionDataAcquisitor::LeapMotionDataAcquisitor(std::unique_ptr<IHandExtractor> handExtractor):
    m_HandExtractor(std::move(handExtractor))
{
}

void LeapMotionDataAcquisitor::Run()
{
    m_Controller.addListener(*this);
}

void LeapMotionDataAcquisitor::Stop()
{
    m_Controller.removeListener(*this);
}

std::vector<Point> LeapMotionDataAcquisitor::ExtractPointClouds(const std::vector<HandPosition>& hands) const
{
    std::vector<Point> pointClouds;
    for(const auto& hand : hands)
    {
        pointClouds.push_back(hand.ElbowPosition);
        pointClouds.push_back(hand.WristPosition);
        pointClouds.push_back(hand.PalmPosition);
        pointClouds.push_back(hand.ThumbPosition);
        pointClouds.push_back(hand.ForeFingerPosition);
        pointClouds.push_back(hand.MiddleFingerPosition);
        pointClouds.push_back(hand.RingFingerPosition);
        pointClouds.push_back(hand.LittleFingerPosition);
    }

    return pointClouds;
}

void LeapMotionDataAcquisitor::onFrame(const Leap::Controller& controller)
{
    const auto frame = controller.frame();
    const auto hands = m_HandExtractor->ExtractFromFrame(frame);
    HandsDetectEvent(hands);
    const auto handsPointClouds = ExtractPointClouds(hands);
    HandsDetectEvent(handsPointClouds);
}
