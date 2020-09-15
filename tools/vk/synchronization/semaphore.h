//
// Created by Владимир on 13.09.2020.
//

#ifndef TOOLS_VK_SYNCHRONIZATION_SEMAPHORE_H
#define TOOLS_VK_SYNCHRONIZATION_SEMAPHORE_H

#include <tools/vk/core.h>
#include <vulkan/vulkan_core.h>

namespace vk
{
	class Semaphore
	{
		public:
		Semaphore ( Core *core );

		virtual ~Semaphore ();

		[[nodiscard]] const VkSemaphore &
		getSemaphore () const;


		private:
		LogicalDevice *device;
		VkSemaphore semaphore;
	};
}// namespace vk
#endif//TOOLS_VK_SYNCHRONIZATION_SEMAPHORE_H
