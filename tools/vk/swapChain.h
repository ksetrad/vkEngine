//
// Created by Владимир on 31.08.2020.
//

#ifndef TOOLS_VK_SWAPCHAIN_H
#define TOOLS_VK_SWAPCHAIN_H

#include <vector>

#include "logicalDevice.h"
#include "tools/vk/physicalDevice.h"
#include <vulkan/vulkan.h>

namespace vk
{
	/// Цепочка смены кадров
	class SwapChain
	{
		public:
			/// Конструктор
			/// \param instance Экземпляр Vulkan
			/// \param physicalDevice Физический интерфейс
			/// \param logicalDevice Логический интерфейс
			SwapChain (
					Instance *instance,
					PhysicalDevice *physicalDevice,
					LogicalDevice *logicalDevice
			);

			/// Деструктор
			~SwapChain ();

			/// Получить необходимый формат для цепочки смены кадров
			/// \param availableFormats Доступные форматы
			/// \return выбранный формат
			VkSurfaceFormatKHR
			chooseSwapSurfaceFormat ( const std::vector < VkSurfaceFormatKHR > &availableFormats );

			/// Получить необходимы режим представления кадров
			/// \param availablePresentModes Доступные режимы
			/// \return выбранный режим
			VkPresentModeKHR
			chooseSwapPresentMode ( const std::vector < VkPresentModeKHR > &availablePresentModes );

			/// Выбрать размер кадра для цепочки смены
			/// \param capabilities Возможности поверхности отображения
			/// \return Размер
			VkExtent2D
			chooseSwapExtent ( const VkSurfaceCapabilitiesKHR &capabilities );

			/// Получить параметры поверхности вывода
			/// \return параметры
			[[nodiscard]] const VkSurfaceFormatKHR &
			getSurfaceFormat () const;

			/// Получить размеры поверхности вывода
			/// \return размеры (геометрические)
			[[nodiscard]] const VkExtent2D &
			getExtent () const;

			/// Получить массив интерфейсов изображений в цепочке кадров
			/// \return Массив интерфейсов
			[[nodiscard]] const std::vector < VkImageView > &
			getImagesView () const;

			VkSwapchainKHR const &
			getSwapChain () const;

		private:
			/// Формат поверхности
			VkSurfaceFormatKHR surfaceFormat;

			/// Размер кадров
			VkExtent2D extent;

			/// Дескриптор цепочки смены кадров
			VkSwapchainKHR swapChain;

			/// Массив изображений цепочки
			std::vector < VkImage > swapChainImages;

			/// Мессив интерфейсов изображений цепочки
			std::vector < VkImageView > swapChainImagesView;

			/// Дескриптор логического интерфейса
			LogicalDevice *logicalDevice;
	};
}// namespace vk
#endif//TOOLS_VK_SWAPCHAIN_H
