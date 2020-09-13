//
// Created by Владимир on 13.09.2020.
//

#ifndef TOOLS_VK_SYNCHRONIZATION_SEMAPHORE_H
#define TOOLS_VK_SYNCHRONIZATION_SEMAPHORE_H

#include <vulkan/vulkan_core.h>
#include <tools/vk/core.h>

namespace vk
{
    class Semaphore
        {
        public:


            Semaphore ( Core* core);

            virtual ~Semaphore ();

            [[nodiscard]] const VkSemaphore  &
            getSemaphore () const;


        private:
            LogicalDevice* device;
            VkSemaphore semaphore;
        };
}
#endif //TOOLS_VK_SYNCHRONIZATION_SEMAPHORE_H
