//
// Created by Владимир on 07.09.2020.
//

#ifndef TOOLS_VK_RENDERPASS_ATTACHMENT_H
#define TOOLS_VK_RENDERPASS_ATTACHMENT_H

#include <vulkan/vulkan.h>

namespace vk::renderpass
{
	class Attachment
	{
		public:
		explicit Attachment ( const VkFormat &swapChainImageFormat )
		{
			/// Формат изображения во вложении
			description.format = swapChainImageFormat;
			/// Количество семплов на пиксель, где сэмпл это количество изображений используемое для вычисление одного пикселя
			/// 1 сэмпл на пиксель
			description.samples = VK_SAMPLE_COUNT_1_BIT;
			/// Как вложение будет обработано при его первом вызове на субпасе , где оно впервые используется
			/// Очистка при загрузке
			description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			/// Как вложение будет обработано при его последнем вызове на субпасе , где оно последний раз используется используется
			/// Вложение будет записано в память
			description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			/// Как трафаретная компонента вложения будет обработана при его первом вызове на субпасе , где оно впервые используется
			/// Не важно
			description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			/// Как трафаретная компонента вложения будет обработана при его последнем вызове на субпасе , где оно последний раз используется
			/// Не важно
			description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			/// Начальное состояние вложения
			/// Неопределенное состояние гвоврит о том что нам нужна только память без учета содержимого в ней
			description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			/// Финальное состояние
			/// Изображение переводится в формат не обходимый для отрисовки на дисплее
			description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		}

		VkAttachmentDescription description;
	};
}// namespace vk::renderpass
#endif//TOOLS_VK_RENDERPASS_ATTACHMENT_H
