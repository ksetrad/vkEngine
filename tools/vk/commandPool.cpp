//
// Created by Владимир on 10.09.2020.
//

#include "tools/vk/commandPool.h"

using namespace vk;

CommandPool::CommandPool ( Core * core ) : logicalDevice(core->getLogicalDevice())
{
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = core->getPhysicalDevice()->getIndices().graphicsFamily.value();
        poolInfo.flags = 0;

        if (vkCreateCommandPool(logicalDevice->getDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
                throw vulkan_exception("failed to create command pool!");
        }
}


CommandPool::~CommandPool ()
{
        vkDestroyCommandPool(logicalDevice->getDevice(), commandPool, nullptr);
}

