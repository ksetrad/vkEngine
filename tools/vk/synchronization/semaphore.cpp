//
// Created by Владимир on 13.09.2020.
//

#include "semaphore.h"

using namespace vk;

VkSemaphore const &
Semaphore::getSemaphore () const
{
	return semaphore;
}

Semaphore::Semaphore ( Core *core ) :
    device ( core->getLogicalDevice () )
{
	VkSemaphoreCreateInfo semaphoreInfo {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	if ( vkCreateSemaphore ( core->getLogicalDevice ()->getDevice (), &semaphoreInfo, nullptr, &semaphore ) != VK_SUCCESS )
		throw std::runtime_error ( "failed to create synchronization objects for a frame!" );
}

Semaphore::~Semaphore ()
{
	vkDestroySemaphore ( device->getDevice (), semaphore, nullptr );
}
