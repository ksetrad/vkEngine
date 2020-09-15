//
// Created by Владимир on 11.09.2020.
//

#ifndef TOOLS_VK_BUFFEROBJECT_H
#define TOOLS_VK_BUFFEROBJECT_H

#include <vulkan/vulkan.h>

#include "tools/vk/core.h"

namespace vk
{
	/// Буферный объект
	class BufferObject
	{
		public:
		enum Type
		{
			/// Вершинный буфер
			VERTEX,
			/// Индексный буфер
			INDEX
		};

		/// Конструктор
		/// \param type Тип буфера
		/// \param core Ядро вулкан
		BufferObject (
		        const Type &type,
		        Core *core );

		virtual ~BufferObject ();

		/// Выделение памяти
		/// \param size размер
		/// \param data блок данных
		/// \param count количество идентичных элементов в буфере
		void
		allocate (
		        unsigned int size,
		        const void *data,
		        const int &count );


		/// Процедура создания буфера
		/// \param core ядро Vulkan
		/// \param size выделяемый размер
		/// \param usage тип использования буфера
		/// \param properties тип использования памяти буфера
		/// \param buffer [out] создаваемый буфер
		/// \param bufferMemory [out] память буфера
		static void
		createBuffer (
		        Core *core,
		        VkDeviceSize size,
		        VkBufferUsageFlags usage,
		        VkMemoryPropertyFlags properties,
		        VkBuffer &buffer,
		        VkDeviceMemory &bufferMemory );

		/// Получить дескриптор буфера GPU
		/// \return дескриптор
		[[nodiscard]] const VkBuffer &
		getBuffer () const;

		/// Получить дескриптор staging-буфера
		/// \return дескриптор
		[[nodiscard]] const VkBuffer &
		getStagingBuffer () const;

		/// Получить размер буфера ( в байтах)
		/// \return размер буфера
		[[nodiscard]] const int &
		size () const;

		/// Получить тип буфера
		/// \return тип
		[[nodiscard]] const Type &
		getType () const;

		/// Получить количество идентичных элементов в буфере
		/// \return количество
		[[nodiscard]] const int &
		count () const;

		private:
		/// Получить тип памяти
		/// \param core ядро Vulkan
		/// \param typeFilter битовая маска влюченных/выключенных типов памяти
		/// \param properties дополнительные свойства памяти
		/// \return индекс нужного типа памяти
		static uint32_t
		findMemoryType (
		        Core *core,
		        uint32_t typeFilter,
		        VkMemoryPropertyFlags properties );

		/// Ядро вулкан
		Core *core;

		/// Тип буфера
		Type type;

		/// Объект буфера
		VkBuffer buffer { VK_NULL_HANDLE };

		/// Память объекта буфера
		VkDeviceMemory bufferMemory { VK_NULL_HANDLE };

		/// Объект когерентного буфера
		VkBuffer stagingBuffer { VK_NULL_HANDLE };

		/// Память когерентного буфер
		VkDeviceMemory stagingBufferMemory { VK_NULL_HANDLE };

		/// Размер буфера ( в байтах )
		int m_size;

		/// Количество элементов в буфере
		int m_count;
	};
}// namespace vk
#endif//TOOLS_VK_BUFFEROBJECT_H
