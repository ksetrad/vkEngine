//
// Created by Владимир on 08.09.2020.
//

#include "viewportstate.h"

using namespace vk::pipeline;

ViewPortState::ViewPortState ( SwapChain * swapChain )
{
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) swapChain->getExtent().width;
        viewport.height = (float) swapChain->getExtent().height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;


        scissor.offset = {0, 0};
        scissor.extent = swapChain->getExtent();

        viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportStateCreateInfo.viewportCount = 1;
        viewportStateCreateInfo.pViewports = &viewport;
        viewportStateCreateInfo.scissorCount = 1;
        viewportStateCreateInfo.pScissors = &scissor;
}

const VkPipelineViewportStateCreateInfo *
ViewPortState::getInfo () const
{
        return &viewportStateCreateInfo;
}

