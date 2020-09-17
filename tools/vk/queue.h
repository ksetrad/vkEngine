//
// Created by Владимир on 12.09.2020.
//

#ifndef TOOLS_VK_QUEUE_H
#define TOOLS_VK_QUEUE_H

#include "logicalDevice.h"

namespace vk
{
	class Queue
	{
		public:
			/// Тип очереди
			enum Type
			{
				/// Очередь для графических операций
				GRAPHIC,
				/// Очередь для операций представления изображения на экране
				PRESENTATION
			};

			/// Очередь
			/// \param logicalDevice Логический интерфейс GPU
			/// \param physicalDevice Физический интерфейс GPU
			/// \param type тип очереди
			Queue (
					LogicalDevice *logicalDevice,
					PhysicalDevice *physicalDevice,
					const Type &type
			);

			/// Получить дескриптор очереди
			/// \return дескриптор
			[[nodiscard]] const VkQueue &
			getQueue () const;

		private:
			/// Дескриптор очереди
			VkQueue queue;

			/// Тип очереди
			Type type;
	};
}// namespace vk
#endif//TOOLS_VK_QUEUE_H
