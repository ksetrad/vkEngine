//
// Created by Владимир on 10.09.2020.
//

#ifndef TOOLS_VK_COMMANDSPOOL_H
#define TOOLS_VK_COMMANDSPOOL_H

#include "tools/vk/bufferObject.h"
#include "tools/vk/core.h"
#include "tools/vk/discriptorsPool.h"
#include "tools/vk/frameBuffer.h"
#include "tools/vk/renderPass.h"


namespace vk
{
	/// Командный пул
	class CommandPool
	{
		public:
		/// Конструктор
		/// \param core ядро Vulkan
		explicit CommandPool ( Core *core );

		virtual ~CommandPool ();

		void
		cmdTransferBuffer ( const BufferObject &buffer );

		virtual void
		setCommandBufferContent ( const VkCommandBuffer &commandBuffer, const VkDescriptorSet *descriptorSet ) = 0;

		/// Создать командный буфер
		/// \param swapChain цепочка смены кадров
		/// \param renderPass проход рендеринга
		/// \param frameBuffer кадровый буфер
		/// \param pool пул дескрипторов
		void
		createCommandBuffer ( SwapChain *swapChain, RenderPass *renderPass, FrameBuffer *frameBuffer, DescriptorsPool *pool );

		const std::vector< VkCommandBuffer > &
		getCommandBuffers () const;

		protected:
		std::vector< VkCommandBuffer > commandBuffers;

		private:
		/// Дескриптор
		VkCommandPool commandPool { VK_NULL_HANDLE };

		/// Ядро Vulkan
		Core *core;
	};
}// namespace vk
#endif//TOOLS_VK_COMMANDSPOOL_H
