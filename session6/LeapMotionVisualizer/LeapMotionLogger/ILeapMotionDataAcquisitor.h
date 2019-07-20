#ifndef ILEAPMOTIONDATAACQUISITOR_H
#define ILEAPMOTIONDATAACQUISITOR_H

#include <vector>
#include <functional>
#include <algorithm>

#include "HandPosition.h"

class ILeapMotionDataAcquisitor
{

public:

    virtual ~ILeapMotionDataAcquisitor() = default;

    class
    {

    public:

        void operator+=(const std::function<void(const std::vector<HandPosition>& hands)>& funcObj)
        {
            m_HandFuncs.push_back(funcObj);
        }

        void operator+=(const std::function<void(const std::vector<Point>& handPointClouds)>& funcObj)
        {
            m_PointCloudsFuncs.push_back(funcObj);
        }

        void operator()(const std::vector<HandPosition>& hands)
        {
            for(const auto& funcObj : m_HandFuncs)
            {
                funcObj(hands);
            }
        }

        void operator()(const std::vector<Point>& handPointClouds)
        {
            for(const auto& funcObj : m_PointCloudsFuncs)
            {
                funcObj(handPointClouds);
            }
        }

    private:

        std::vector<std::function<void(const std::vector<HandPosition>& hands)>> m_HandFuncs;
        std::vector<std::function<void(const std::vector<Point>& hands)>> m_PointCloudsFuncs;

    } HandsDetectEvent;

};

#endif // ILEAPMOTIONDATAACQUISITOR_H
