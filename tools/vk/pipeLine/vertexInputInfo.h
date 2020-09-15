//
// Created by Владимир on 09.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_VERTEXINPUTINFO_H
#define TOOLS_VK_PIPELINE_VERTEXINPUTINFO_H

#include "tools/vk/common/vertex.h"

namespace vk::pipeline
{
	/// Параметры входных вершин конвеера
	class VertexInputInfo
	{
		public:
		/// Конструктор
		VertexInputInfo ();

		/// Получить параметры входных вершин
		/// \return Указатель
		VkPipelineVertexInputStateCreateInfo *
		getInfo ();

		private:
		VkPipelineVertexInputStateCreateInfo inputInfo {};

		VkVertexInputBindingDescription bindingDescription;

		std::array< VkVertexInputAttributeDescription, 3 > attributeDescriptions;
	};
}// namespace vk::pipeline
#endif//TOOLS_VK_PIPELINE_VERTEXINPUTINFO_H
