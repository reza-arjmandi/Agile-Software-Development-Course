#include "HandExtractor.h"
#include <QDebug>
std::vector<HandPosition> HandExtractor::ExtractFromFrame(const Leap::Frame &frame)
{
    const auto hands = frame.hands();
    std::vector<HandPosition> extractedHands;

    for(const auto& hand : hands)
    {
        HandPosition extractedHand;

        const auto arm = hand.arm();

        const auto elbow = arm.elbowPosition();
        extractedHand.ElbowPosition.X = elbow.x;
        extractedHand.ElbowPosition.Y = elbow.y;
        extractedHand.ElbowPosition.Z = elbow.z;

        const auto wrist = arm.wristPosition();
        extractedHand.WristPosition.X = wrist.x;
        extractedHand.WristPosition.Y = wrist.y;
        extractedHand.WristPosition.Z = wrist.z;

        const auto palm = hand.palmPosition();
        extractedHand.PalmPosition.X = palm.x;
        extractedHand.PalmPosition.Y = palm.y;
        extractedHand.PalmPosition.Z = palm.z;

        for(const auto& finger : hand.fingers())
        {
            if(finger.type() == Leap::Finger::Type::TYPE_THUMB)
            {
                const auto thumb = finger.tipPosition();
                extractedHand.ThumbPosition.X = thumb.x;
                extractedHand.ThumbPosition.Y = thumb.y;
                extractedHand.ThumbPosition.Z = thumb.z;
            }
            else if (finger.type() == Leap::Finger::Type::TYPE_INDEX)
            {
                const auto foreFinger = finger.tipPosition();
                extractedHand.ForeFingerPosition.X = foreFinger.x;
                extractedHand.ForeFingerPosition.Y = foreFinger.y;
                extractedHand.ForeFingerPosition.Z = foreFinger.z;
            }
            else if(finger.type() == Leap::Finger::Type::TYPE_MIDDLE)
            {
                const auto middleFinger = finger.tipPosition();
                extractedHand.MiddleFingerPosition.X = middleFinger.x;
                extractedHand.MiddleFingerPosition.Y = middleFinger.y;
                extractedHand.MiddleFingerPosition.Z = middleFinger.z;
            }
            else if(finger.type() == Leap::Finger::Type::TYPE_RING)
            {
                const auto ringFinger = finger.tipPosition();
                extractedHand.RingFingerPosition.X = ringFinger.x;
                extractedHand.RingFingerPosition.Y = ringFinger.y;
                extractedHand.RingFingerPosition.Z = ringFinger.z;
            }
            else if(finger.type() == Leap::Finger::Type::TYPE_PINKY)
            {
                const auto littleFinger = finger.tipPosition();
                extractedHand.LittleFingerPosition.X = littleFinger.x;
                extractedHand.LittleFingerPosition.Y = littleFinger.y;
                extractedHand.LittleFingerPosition.Z = littleFinger.z;
            }
        }
        extractedHands.push_back(extractedHand);
    }
    return extractedHands;
}
