//
// Created by Владимир on 06.09.2020.
//

#include "tools/vk/renderPass.h"

using namespace vk;

RenderPass::RenderPass (
		Core *core
) :
		device ( core->getLogicalDevice () )
{
}

RenderPass::~RenderPass ()
{
	vkDestroyRenderPass ( device->getDevice (), renderPass, nullptr );
}

const VkRenderPass &
RenderPass::getRenderPass () const
{
	return renderPass;
}
