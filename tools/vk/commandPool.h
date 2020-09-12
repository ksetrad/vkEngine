//
// Created by Владимир on 10.09.2020.
//

#ifndef TOOLS_VK_COMMANDPOOL_H
#define TOOLS_VK_COMMANDPOOL_H

#include "tools/vk/core.h"


namespace vk
{
    /// Командный пул
    class CommandPool
        {
        public:
            /// Конструктор
            /// \param core ядро Vulkan
            explicit
            CommandPool ( Core * core);

            virtual
            ~CommandPool ();

        private:
            /// Дескриптор
            VkCommandPool commandPool { VK_NULL_HANDLE };

            /// Логический интерфейс GPU
            LogicalDevice * logicalDevice;
        };
}
#endif //TOOLS_VK_COMMANDPOOL_H
