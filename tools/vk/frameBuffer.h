//
// Created by Владимир on 10.09.2020.
//

#ifndef TOOLS_VK_FRAMEBUFFER_H
#define TOOLS_VK_FRAMEBUFFER_H

#include "tools/vk/renderPass.h"

namespace vk
{
	/// Кадровый буфер
	class FrameBuffer
	{
		public:
			/// Кадровый буфер
			/// \param core ядро Vulkan
			/// \param renderPass проход рендеринга
			FrameBuffer (
					Core *core,
					RenderPass *renderPass
			);

			virtual ~FrameBuffer ();

			const std::vector < VkFramebuffer > &
			getFrameBuffers () const;

		private:
			/// Логический интерфейс GPU
			LogicalDevice *logicalDevice;

			/// Массив кадровых буферов (по элементу на каждый кадр цепочки смены кадров)
			std::vector < VkFramebuffer > swapChainFramebuffers;
	};
}// namespace vk
#endif//TOOLS_VK_FRAMEBUFFER_H
