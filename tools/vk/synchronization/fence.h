//
// Created by Владимир on 13.09.2020.
//

#ifndef TOOLS_VK_SYNCHRONIZATION_FENCE_H
#define TOOLS_VK_SYNCHRONIZATION_FENCE_H

#include <tools/vk/core.h>

namespace vk
{
	class Fence
	{
		public:
		explicit Fence ( Core *core );

		virtual ~Fence ();

		VkFence const &
		getFence () const;

		void
		wait ();

		private:
		VkFence fence { VK_NULL_HANDLE };

		LogicalDevice *device;
	};
}// namespace vk
#endif//TOOLS_VK_SYNCHRONIZATION_FENCE_H
