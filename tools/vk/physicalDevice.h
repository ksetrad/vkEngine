//
// Created by Владимир on 26.08.2020.
//

#ifndef TOOLS_VK_PHYSICALDEVICE_H
#define TOOLS_VK_PHYSICALDEVICE_H

#include <optional>
#include <vulkan/vulkan.h>

#include "tools/vk/instance.h"

namespace vk
{
	/// Физический интерфейс GPU
	class PhysicalDevice
	{
		public:
		/// Параметры очередей на устройстве
		struct QueueFamilyIndices {
			/// Графическое семейство
			std::optional< uint32_t > graphicsFamily;
			/// Семейство презентации изображений
			std::optional< uint32_t > presentFamily;

			/// Функция проверки установленности всех индексов в структуре
			/// \return Результат проверки
			[[nodiscard]] bool
			isComplete () const
			{
				return graphicsFamily.has_value () && presentFamily.has_value ();
			}
		};
		/// Конструктор
		/// \param instance Экземпляр Vulakan
		explicit PhysicalDevice ( Instance *instance );

		/// Получить индексы семейств очередей
		/// \return Структура индексов
		[[nodiscard]] const QueueFamilyIndices &
		getIndices () const;

		/// Получить выбранное физическое устройство
		/// \return Физическое устройство
		[[nodiscard]] const VkPhysicalDevice &
		getPhysicalDevice () const;

		private:
		/// Функция поиска графического физического устройства(GPU)
		/// \return физическое устройство
		VkPhysicalDevice
		findDevice ();

		/// Найти индексы семейств очередей на GPU
		void
		findQueueIndices ();

		/// Проверить поддерживает ли устройство заданные расширения
		/// \param device Физическое устройство
		/// \return результат проверки
		bool
		checkExtensionSupport ( const VkPhysicalDevice &device );

		/// Экземпляр Vulkan
		Instance *instance;

		/// Индексы семейств очередей на видеокарте
		QueueFamilyIndices indices;

		/// Используемое физическое устройство
		VkPhysicalDevice physicalDevice { VK_NULL_HANDLE };
	};
}// namespace vk
#endif//TOOLS_VK_PHYSICALDEVICE_H
