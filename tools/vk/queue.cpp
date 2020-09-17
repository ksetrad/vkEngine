//
// Created by Владимир on 12.09.2020.
//

#include "tools/vk/queue.h"

using namespace vk;

Queue::Queue (
		LogicalDevice *logicalDevice,
		PhysicalDevice *physicalDevice,
		const Queue::Type &type
) :
		type ( type )
{
	switch ( type )
	{
		case GRAPHIC:
			vkGetDeviceQueue ( logicalDevice->getDevice (), physicalDevice->getIndices ().graphicsFamily.value (), 0,
			                   &queue );
			break;
		case PRESENTATION:
			vkGetDeviceQueue ( logicalDevice->getDevice (), physicalDevice->getIndices ().presentFamily.value (), 0,
			                   &queue );
			break;
	}
}

const VkQueue &
Queue::getQueue () const
{
	return queue;
}
