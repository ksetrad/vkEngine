//
// Created by Владимир on 11.09.2020.
//

#include "tools/vk/bufferObject.h"

using namespace vk;

void
BufferObject::allocate (
        int size ,
        void * data
                       )
{
        /// Формируем когерентный буфер в оперативке
        createBuffer ( core, size , VK_BUFFER_USAGE_TRANSFER_SRC_BIT ,
                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT , stagingBuffer ,
                       stagingBufferMemory );

        /// Заполняем его данными
        void * staging_data;
        vkMapMemory ( core->getLogicalDevice()->getDevice() , stagingBufferMemory , 0 , size , 0 , & staging_data );
        memcpy ( staging_data , data , size );
        vkUnmapMemory ( core->getLogicalDevice()->getDevice() , stagingBufferMemory );

        switch ( type )
        {
                /// Формируем буферы на устройстве
                case INDEX:
                        createBuffer ( core, size ,
                                       VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT ,
                                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT , buffer , bufferMemory );
                        break;
                case VERTEX:
                        createBuffer ( core, size , VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT ,
                                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT , buffer , bufferMemory );
                        break;
        }
}

BufferObject::BufferObject (
        const BufferObject::Type & type ,
        Core * core
                           )
        : core ( core ) , type ( type )
{

}

void
BufferObject::createBuffer (
        Core * core,
        VkDeviceSize size ,
        VkBufferUsageFlags usage ,
        VkMemoryPropertyFlags properties ,
        VkBuffer & buffer ,
        VkDeviceMemory & bufferMemory
                           )
{
        /// Формируем структуру буфера
        VkBufferCreateInfo bufferInfo { };
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        /// Устанавливаем размер буфера
        bufferInfo.size = size;
        /// Задаем тип использования
        bufferInfo.usage = usage;
        /// Указываем существует ли к буферу конкурентный доступ
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        /// Создаем буфер
        if ( vkCreateBuffer ( core->getLogicalDevice()->getDevice() , & bufferInfo , nullptr , & buffer ) != VK_SUCCESS )
        {
                throw vulkan_exception ( "failed to create buffer!" );
        }

        /// Получаем требования памяти к созданному буферу
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements ( core->getLogicalDevice()->getDevice() , buffer , & memRequirements );

        /// Формируем структуру для выделения памяти
        VkMemoryAllocateInfo allocInfo { };
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        /// Определяем индекс требуемой памяти
        allocInfo.memoryTypeIndex = findMemoryType ( core, memRequirements.memoryTypeBits , properties );

        /// Выделяем память под буфер
        if ( vkAllocateMemory ( core->getLogicalDevice()->getDevice() , & allocInfo , nullptr , & bufferMemory ) != VK_SUCCESS )
        {
                throw vulkan_exception ( "failed to allocate buffer memory!" );
        }

        /// Привязываем память к буферу
        vkBindBufferMemory(core->getLogicalDevice()->getDevice(), buffer, bufferMemory, 0);
}

uint32_t
BufferObject::findMemoryType (
        Core * core,
        uint32_t typeFilter ,
        VkMemoryPropertyFlags properties
                             )
{
        /// Получаем параметры памяти выбранного физического устройства
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(core->getPhysicalDevice()->getPhysicalDevice(), &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
                /// В typeFilter каждый бит отвечает за конкретный тип памяти, следовательно перебираются биты по одному (1 << i) и проверяется включен ли бит в фильтре
                /// Плюс проверяем флаги
                if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                        return i;
                }
        }
        /// Память не найдена - исключение
        throw vulkan_exception("failed to find suitable memory type!");
}

