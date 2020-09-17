//
// Created by Владимир on 11.09.2020.
//

#include "uniformBufferSet.h"
#include "bufferObject.h"
#include <cstring>
using namespace vk;

UniformBufferSet::UniformBufferSet (
		Core *core,
		const size_t &size
) :
		device ( core->getLogicalDevice () )
{
	/// Число буфферов (и связанных с ними блоков памяти) равно число кадров в цепочке
	buffers.resize ( core->getSwapChain ()->getImagesView ().size () );
	buffersMemmory.resize ( core->getSwapChain ()->getImagesView ().size () );

	/// Формируем буферы под каждый кадр
	for ( size_t i = 0 ;
	      i < buffers.size () ;
	      i++ )
	{
		BufferObject::createBuffer ( core, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		                             VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		                             VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		                             buffers[ i ], buffersMemmory[ i ] );
	}
}

UniformBufferSet::~UniformBufferSet ()
{
	for ( size_t i = 0 ;
	      i < buffers.size () ;
	      i++ )
	{
		vkDestroyBuffer ( device->getDevice (), buffers[ i ], nullptr );
		vkFreeMemory ( device->getDevice (), buffersMemmory[ i ], nullptr );
	}
}

const std::vector < VkBuffer > &
UniformBufferSet::getBuffers () const
{
	return buffers;
}

void
UniformBufferSet::write (
		const int &id,
		void *data,
		int size
)
{
	void *dst_data;

	vkMapMemory ( device->getDevice (), buffersMemmory[ id ], 0, size, 0, &dst_data );
	memcpy ( dst_data, data, size );
	vkUnmapMemory ( device->getDevice (), buffersMemmory[ id ] );
}
