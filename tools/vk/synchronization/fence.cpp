//
// Created by Владимир on 13.09.2020.
//

#include "fence.h"

using namespace vk;

Fence::Fence ( Core * core )
        : device ( core->getLogicalDevice () )
{
        VkFenceCreateInfo fenceInfo { };
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        if ( vkCreateFence ( core->getLogicalDevice ()->getDevice () , & fenceInfo , nullptr , & fence ) != VK_SUCCESS )
        {
                throw vulkan_exception ( "failed to create synchronization objects for a frame!" );
        }
}

Fence::~Fence ()
{
        vkDestroyFence ( device->getDevice () , fence , nullptr );
}

VkFence const &
Fence::getFence () const
{
        return fence;
}

void
Fence::wait ()
{
        vkWaitForFences(device->getDevice(), 1, &fence, VK_TRUE, UINT64_MAX);
}

