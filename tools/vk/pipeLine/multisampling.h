//
// Created by Владимир on 06.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_MULTISAMPLING_H
#define TOOLS_VK_PIPELINE_MULTISAMPLING_H
#include <vulkan/vulkan.h>
namespace vk::pipeline
{
	/// Анти-алиазинг
	class Multisampling
	{
		public:
		explicit
		        /// Конструктор
		        /// \param isEnable признак включения
		        Multisampling ( const bool &isEnable );

		/// Получить указатель на структуру
		/// \return указатель
		VkPipelineMultisampleStateCreateInfo *
		getInfo ();

		private:
		/// Структура параметров
		VkPipelineMultisampleStateCreateInfo createInfo {};
	};
}// namespace vk::pipeline
#endif//TOOLS_VK_PIPELINE_MULTISAMPLING_H
