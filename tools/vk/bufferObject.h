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
                    VERTEX ,
                    /// Индексный буфер
                    INDEX
                };

            /// Конструктор
            /// \param type Тип буфера
            /// \param core Ядро вулкан
            BufferObject (
                    const Type & type ,
                    Core * core
                         );

            /// Выделение памяти
            /// \param size размер
            /// \param data блок данных
            void
            allocate (
                    int size ,
                    void * data
                     );


            /// Процедура создания буфера
            /// \param core ядро Vulkan
            /// \param size выделяемый размер
            /// \param usage тип использования буфера
            /// \param properties тип использования памяти буфера
            /// \param buffer [out] создаваемый буфер
            /// \param bufferMemory [out] память буфера
            static
            void
            createBuffer (
                    Core * core ,
                    VkDeviceSize size ,
                    VkBufferUsageFlags usage ,
                    VkMemoryPropertyFlags properties ,
                    VkBuffer & buffer ,
                    VkDeviceMemory & bufferMemory
                         );

        private:
            /// Получить тип памяти
            /// \param core ядро Vulkan
            /// \param typeFilter битовая маска влюченных/выключенных типов памяти
            /// \param properties дополнительные свойства памяти
            /// \return индекс нужного типа памяти
            static
            uint32_t
            findMemoryType (
                    Core * core ,
                    uint32_t typeFilter ,
                    VkMemoryPropertyFlags properties
                           );

            /// Ядро вулкан
            Core * core;

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
        };
}
#endif //TOOLS_VK_BUFFEROBJECT_H
