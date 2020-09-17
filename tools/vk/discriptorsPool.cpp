//
// Created by Владимир on 12.09.2020.
//

#include "discriptorsPool.h"
#include <tools/vk/pipeLine/pipeLineLayout.h>

using namespace vk;

DescriptorsPool::DescriptorsPool ( vk::Core *core ) :
		core ( core )
{
	VkDescriptorPoolSize poolSize { };
	poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize.descriptorCount = static_cast< uint32_t > ( core->getSwapChain ()->getImagesView ().size () );

	VkDescriptorPoolCreateInfo poolInfo { };
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = 1;
	poolInfo.pPoolSizes = &poolSize;
	poolInfo.maxSets = static_cast< uint32_t > ( core->getSwapChain ()->getImagesView ().size () );

	if ( vkCreateDescriptorPool ( core->getLogicalDevice ()->getDevice (), &poolInfo, nullptr,
	                              &descriptorPool ) != VK_SUCCESS )
	{
		throw std::runtime_error ( "failed to create descriptor pool!" );
	}
}

DescriptorsPool::~DescriptorsPool ()
{
	vkDestroyDescriptorPool ( core->getLogicalDevice ()->getDevice (), descriptorPool, nullptr );
}

void
DescriptorsPool::createDescritorSets (
		const std::vector < VkBuffer > &ubo_vector,
		const pipeline::PipeLineLayout *layout,
		const int &size
)
{
	std::vector < VkDescriptorSetLayout > layouts ( core->getSwapChain ()->getImagesView ().size (),
	                                                *layout->getDescriptorSetLayout ().getLayout () );
	VkDescriptorSetAllocateInfo allocInfo { };
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = static_cast< uint32_t > ( core->getSwapChain ()->getImagesView ().size () );
	allocInfo.pSetLayouts = layouts.data ();

	descriptorSets.resize ( core->getSwapChain ()->getImagesView ().size () );

	if ( vkAllocateDescriptorSets ( core->getLogicalDevice ()->getDevice (), &allocInfo,
	                                descriptorSets.data () ) != VK_SUCCESS )
	{
		throw vulkan_exception ( "failed to allocate descriptor sets!" );
	}

	for ( size_t i = 0 ;
	      i < descriptorSets.size () ;
	      i++ )
	{
		VkDescriptorBufferInfo bufferInfo { };
		bufferInfo.buffer = ubo_vector[ i ];
		bufferInfo.offset = 0;
		bufferInfo.range = size;

		VkWriteDescriptorSet descriptorWrite { };
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSets[ i ];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;

		vkUpdateDescriptorSets ( core->getLogicalDevice ()->getDevice (), 1, &descriptorWrite, 0,
		                         nullptr );
	}
}

const std::vector < VkDescriptorSet > &
DescriptorsPool::getDescriptorSets () const
{
	return descriptorSets;
}
