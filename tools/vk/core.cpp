//
// Created by Владимир on 26.08.2020.
//

#include "core.h"

using namespace vk;

Core::Core ()
{
        instance = new Instance();
//        LogicalDevice* logicalDevice;
//        PhysicalDevice* physicalDevice;
}

Core::~Core ()
{
        delete instance;
}

