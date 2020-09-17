//
// Created by Владимир on 08.09.2020.
//

#include "pipeLineLayout.h"
#include "descriptorSetLayout.h"
#include "tools/vk/logicalDevice.h"

using namespace vk::pipeline;

PipeLineLayout::PipeLineLayout (
		vk::LogicalDevice *logicalDevice
) :
		logicalDevice ( logicalDevice ),
		descriptorSetLayout ( logicalDevice )
{

	VkPipelineLayoutCreateInfo pipelineLayoutInfo { };
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayout.getLayout ();

	if ( vkCreatePipelineLayout ( logicalDevice->getDevice (), &pipelineLayoutInfo, nullptr, &layout ) !=
	     VK_SUCCESS )
	{
		throw vulkan_exception ( "failed to create pipeline layout!" );
	}
}

const VkPipelineLayout &
PipeLineLayout::getLayout () const
{
	return layout;
}

PipeLineLayout::~PipeLineLayout ()
{
	vkDestroyDescriptorSetLayout ( logicalDevice->getDevice (), *descriptorSetLayout.getLayout (), nullptr );
	vkDestroyPipelineLayout ( logicalDevice->getDevice (), layout, nullptr );
}

const DescriptorSetLayout &
PipeLineLayout::getDescriptorSetLayout () const
{
	return descriptorSetLayout;
}
