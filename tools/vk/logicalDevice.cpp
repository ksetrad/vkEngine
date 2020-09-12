//
// Created by Владимир on 26.08.2020.
//
#include <set>
#include "tools/configuration.h"

#include "tools/vk/logicalDevice.h"

using namespace vk;

const VkDevice &
LogicalDevice::getDevice () const
{
        return device;
}

LogicalDevice::LogicalDevice (
        Instance * instance ,
        PhysicalDevice * physicalDevice
                             )
        : instance ( instance ) , physicalDevice ( physicalDevice )
{
        /// Формируем набор уникальных индексов семейств очередей физического устройства
        std::set < uint32_t > uniqueQueueFamilies = { physicalDevice->getIndices ().graphicsFamily.value () ,
                                                      physicalDevice->getIndices ().presentFamily.value () };

        /// Формируем массив структур с информацией об семействах очередей
        std::vector < VkDeviceQueueCreateInfo > queueCreateInfos;
        /// Приоритет очереди ( пока у нас только по одному набору очередей - приоритет актуален равным 1)
        float queuePriority = 1.0f;
        for ( uint32_t queueFamily : uniqueQueueFamilies )
        {
                VkDeviceQueueCreateInfo queueCreateInfo { };
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = queueFamily;
                queueCreateInfo.queueCount = 1;
                queueCreateInfo.pQueuePriorities = & queuePriority;
                queueCreateInfos.push_back ( queueCreateInfo );
        }

        /// В данный момент особые возможности физического устройства нас не интересуют
        VkPhysicalDeviceFeatures deviceFeatures { };

        /// Формируем структуру параметров логического устройства
        VkDeviceCreateInfo createInfo { };
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        /// Устанавливаем параметры семейств очередей
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size ());
        createInfo.pQueueCreateInfos = queueCreateInfos.data ();

        /// Устанавливаем параметры особых возможностей GPU (пока нет (и не будет наверно))
        createInfo.pEnabledFeatures = & deviceFeatures;

        /// Устанавливаем требуемые расширения
        auto deviceExtensions = Configuration::vulkan ().getDeviceExtensions ();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size ());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data ();

#ifdef VULKAN_DEBUG
        /// В режиме DEBUG подключаем необходимые слои валидации
        auto validationLayers = Configuration::vulkan ().getValidationLayersArr ();
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size ());
        createInfo.ppEnabledLayerNames = validationLayers.data ();
#else
        createInfo.enabledLayerCount = 0;
#endif

        /// Создаем логический интерфейс GPU
        if ( vkCreateDevice ( physicalDevice->getPhysicalDevice () , & createInfo , nullptr , & device ) != VK_SUCCESS )
        {
                throw vulkan_exception( "failed to create logical device!" );
        }
}

LogicalDevice::~LogicalDevice ()
{
        /// Разрушаем логический интерфейс
        vkDestroyDevice(device, nullptr);
}
