//
// Created by Владимир on 10.09.2020.
//

#include "commandPool.h"

using namespace engine;

CommandPool::CommandPool ( vk::Core * core )
        : vk::CommandPool ( core->getPhysicalDevice () , core->getLogicalDevice () )
{

}

