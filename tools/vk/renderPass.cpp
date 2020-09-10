//
// Created by Владимир on 06.09.2020.
//

#include "tools/vk/renderPass.h"
#include "swapChain.h"
#include "logicalDevice.h"

using namespace vk;

RenderPass::RenderPass (
        LogicalDevice * device ,
        SwapChain * swapChain
                       )
        : device ( device ) , swapChain ( swapChain )
{

}

RenderPass::~RenderPass ()
{
        vkDestroyRenderPass ( device->getDevice() , renderPass , nullptr );
}

const VkRenderPass &
RenderPass::getRenderPass () const
{
        return renderPass;
}
