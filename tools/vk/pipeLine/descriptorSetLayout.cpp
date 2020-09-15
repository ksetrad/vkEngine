//
// Created by Владимир on 08.09.2020.
//

#include "descriptorSetLayout.h"
#include <tools/vk/logicalDevice.h>

using namespace vk::pipeline;

DescriptorSetLayout::DescriptorSetLayout ( LogicalDevice *device )
{
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.pImmutableSamplers = nullptr;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutCreateInfo layoutInfo {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &uboLayoutBinding;

	if ( vkCreateDescriptorSetLayout ( device->getDevice (), &layoutInfo, nullptr, &layout ) != VK_SUCCESS )
	{
		throw vulkan_exception ( "failed to create descriptor set layout!" );
	}
}

const VkDescriptorSetLayout *
DescriptorSetLayout::getLayout () const
{
	return &layout;
}
