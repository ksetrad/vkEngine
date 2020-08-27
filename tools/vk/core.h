//
// Created by Владимир on 26.08.2020.
//

#ifndef TOOLS_VK_CORE_H
#define TOOLS_VK_CORE_H

#include "instance.h"
#include "logicalDevice.h"
#include "physicalDevice.h"

namespace vk
{
    class Core
        {
        public:
            Core();
            ~Core();
        private:
                Instance* instance;
                LogicalDevice* logicalDevice;
                PhysicalDevice* physicalDevice;
        };
}
#endif //TOOLS_VK_CORE_H
