//
// Created by Владимир on 26.08.2020.
//

#ifndef TOOLS_VK_CORE_H
#define TOOLS_VK_CORE_H

#include "instance.h"
#include "logicalDevice.h"
#include "physicalDevice.h"
#include "swapChain.h"

namespace vk
{
    class Core
        {
        public:
            Core ();

            ~Core ();

        private:
            /// Окно
            GLFWwindow * window;

            /// Экземпляр Vulkan
            Instance * instance;
            
            /// Логическое устройство
            LogicalDevice * logicalDevice;

            /// Физическое устройство
            PhysicalDevice * physicalDevice;

            /// Цепочка смены кадров
            SwapChain* swapChain;
        };
}
#endif //TOOLS_VK_CORE_H
