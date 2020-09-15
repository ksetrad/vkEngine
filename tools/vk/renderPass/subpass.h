//
// Created by Владимир on 07.09.2020.
//

#ifndef TOOLS_VK_RENDERPASS_SUBPASS_H
#define TOOLS_VK_RENDERPASS_SUBPASS_H

#include <vulkan/vulkan.h>

namespace vk::renderpass
{
	class SubPass
	{
		public:
		explicit SubPass ( const VkFormat &swapChainImageFormat, VkAttachmentReference *colorAttachmentRef )
		{
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			subpass.colorAttachmentCount = 1;
			subpass.pColorAttachments = colorAttachmentRef;
		}

		VkSubpassDescription subpass {};
	};
}// namespace vk::renderpass
#endif//TOOLS_VK_RENDERPASS_SUBPASS_H
