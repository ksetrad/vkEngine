//
// Created by Владимир on 08.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_DESCRIPTORSETLAYOUT_H
#define TOOLS_VK_PIPELINE_DESCRIPTORSETLAYOUT_H

#include <vulkan/vulkan.h>

namespace vk
{
	class LogicalDevice;

	namespace pipeline
	{
		/// Макет набора дескрипторов
		class DescriptorSetLayout
		{
			public:
				/// Конструктор
				/// \param device логическое устройство
				DescriptorSetLayout ( LogicalDevice *device );

				/// Получить указатель на макет набора дескрипторов
				/// \return указатель
				const VkDescriptorSetLayout *
				getLayout () const;

			private:
				/// Структура параметров макета
				VkDescriptorSetLayout layout;

				/// Привязка макета дескрипторов
				VkDescriptorSetLayoutBinding uboLayoutBinding { };
		};
	}// namespace pipeline
}// namespace vk
#endif//TOOLS_VK_PIPELINE_DESCRIPTORSETLAYOUT_H
