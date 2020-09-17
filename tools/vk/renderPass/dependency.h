//
// Created by Владимир on 07.09.2020.
//

#ifndef TOOLS_VK_RENDERPASS_DEPENDENCY_H
#define TOOLS_VK_RENDERPASS_DEPENDENCY_H
namespace vk::renderpass
{
	class SubPassDependency
	{
		public:
			explicit SubPassDependency ()
			{
				dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
				dependency.dstSubpass = 0;
				dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				dependency.srcAccessMask = 0;
				dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			}

			VkSubpassDependency dependency { };
	};
}// namespace vk::renderpass
#endif//TOOLS_VK_RENDERPASS_DEPENDENCY_H
