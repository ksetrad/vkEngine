//
// Created by Владимир on 06.09.2020.
//

#include "blending.h"
#include <vulkan/vulkan.h>

vk::pipeline::Blending::Blending (
		const bool &isEnable
)
{

	colorBlendAttachment.colorWriteMask =
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_TRUE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;


	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	createInfo.logicOpEnable = VK_FALSE;
	createInfo.logicOp = VK_LOGIC_OP_COPY;
	createInfo.attachmentCount = 1;
	createInfo.pAttachments = &colorBlendAttachment;
	createInfo.blendConstants[ 0 ] = 0.0f;
	createInfo.blendConstants[ 1 ] = 0.0f;
	createInfo.blendConstants[ 2 ] = 0.0f;
	createInfo.blendConstants[ 3 ] = 0.0f;
}

VkPipelineColorBlendStateCreateInfo *
vk::pipeline::Blending::getInfo ()
{
	return &createInfo;
}
