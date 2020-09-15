//
// Created by Владимир on 06.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_BLENDING_H
#define TOOLS_VK_PIPELINE_BLENDING_H

#include <vulkan/vulkan.h>

namespace vk::pipeline
{
	/// Функционал смешивания цветов
	class Blending
	{
		public:
		/// Конструктор
		/// \param isEnable признак включения смешивания
		explicit Blending (
		        const bool &isEnable );

		/// Получить указатель на структуру
		/// \return указатель
		VkPipelineColorBlendStateCreateInfo *
		getInfo ();

		private:
		VkPipelineColorBlendAttachmentState colorBlendAttachment {};
		/// Структура свойств
		VkPipelineColorBlendStateCreateInfo createInfo {};
	};
}// namespace vk::pipeline
#endif//TOOLS_VK_PIPELINE_BLENDING_H
