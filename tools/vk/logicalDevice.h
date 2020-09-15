//
// Created by Владимир on 26.08.2020.
//

#ifndef TOOLS_VK_LOGICALDEVICE_H
#define TOOLS_VK_LOGICALDEVICE_H

#include "tools/vk/physicalDevice.h"

namespace vk
{
	/// Логический интерфейс GPU
	class LogicalDevice
	{
		public:
		/// Конструктор
		/// \param instance указатель на объект экземпляра Vulkan
		/// \param physicalDevice указатель на объект физического интерфейса GPU
		LogicalDevice (
		        Instance *instance,
		        PhysicalDevice *physicalDevice );

		/// Получить логический интерфейс
		/// \return Интерфейс
		[[nodiscard]] const VkDevice &
		getDevice () const;

		/// Деструктор
		virtual ~LogicalDevice ();

		private:
		/// Дескриптор логического интерфейса
		VkDevice device { VK_NULL_HANDLE };

		/// Указатель на экземпляр Vulkan
		Instance *instance;

		/// Указатель на экземпляр интерфейса физического устройства
		PhysicalDevice *physicalDevice;
	};
}// namespace vk
#endif//TOOLS_VK_LOGICALDEVICE_H
