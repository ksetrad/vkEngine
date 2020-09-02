//
// Created by Владимир on 26.08.2020.
//
#include <vector>
#include <set>
#include <tools/exceptions.h>
#include <iostream>
#include <tools/logger.h>
#include <tools/configuration.h>
#include "physicalDevice.h"

using namespace vk;

PhysicalDevice::PhysicalDevice ( Instance * instance )
        : instance ( instance )
{
        /// Выбираем подходящее графическое устройство
        physicalDevice = findDevice ();
        /// Проверяем наличие физического устройства
        verify( ( physicalDevice != nullptr ) , "physicalDevice not found" );
        /// Настраиваем индексы очередей
        findQueueIndices ();
        verify( indices.isComplete () , "not all queue family funded" );
}

VkPhysicalDevice
PhysicalDevice::findDevice ()
{
        /// Вычисляем количество доступных в системе графических устройств (GPU)
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices ( instance->getInstance () , & deviceCount , nullptr );
        verify ( ( deviceCount != 0 ) , "device not found" );
        /// Заполняем массив устройств
        std::vector < VkPhysicalDevice > devices ( deviceCount );
        vkEnumeratePhysicalDevices ( instance->getInstance () , & deviceCount , devices.data () );
        /// Ищем в списке устройств подходящее
        for ( int i = 0 ;
              i < deviceCount ;
              i++ )
        {
                /// Получаем свойства устройства
                VkPhysicalDeviceProperties deviceProperties;
                vkGetPhysicalDeviceProperties ( devices[ i ] , & deviceProperties );
                /// Получаем функционал устройства
                VkPhysicalDeviceFeatures deviceFeatures;
                vkGetPhysicalDeviceFeatures ( devices[ i ] , & deviceFeatures );
                Logger::message ( Logger::info , Logger::Alias ( "FULL" ) , "find GPU " , deviceProperties.deviceName );
                /// Проверяем запрошенные параметры GPU
                if ( deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
                     && deviceFeatures.geometryShader && checkExtensionSupport ( devices[ i ] ) &&
                     instance->getSurface ()->getSwapChainDetails ( devices[ i ] ).isComplete () )
                {
                        return devices[ i ];
                }
        }
        /// Устройство не найдено - возврщаем нулевой указатель
        return nullptr;
}

void
PhysicalDevice::findQueueIndices ()
{
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties ( physicalDevice , & queueFamilyCount , nullptr );

        std::vector < VkQueueFamilyProperties > queueFamilies ( queueFamilyCount );
        vkGetPhysicalDeviceQueueFamilyProperties ( physicalDevice , & queueFamilyCount , queueFamilies.data () );
        /// Определяем индексы семейств очередей
        int i = 0;
        for ( const auto & queueFamily : queueFamilies )
        {
                /// Определяем относится ли рассматриваемое семейство к графическим семействам очередей
                if ( queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT )
                {
                        indices.graphicsFamily = i;
                }
                /// Проверяем возможно ли с помощью данного семейства отображать изображения на поверхность
                if ( instance->getSurface ()->checkPresent ( physicalDevice , i ) )
                {
                        indices.presentFamily = i;
                }
                /// Если все индексы установлены - выходим из цикла
                if ( indices.isComplete () )
                {
                        break;
                }
                i++;
        }
}

bool
PhysicalDevice::checkExtensionSupport ( VkPhysicalDevice const & device )
{
        /// Получаем набор доступных расширений для физического устройства
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties ( device , nullptr , & extensionCount , nullptr );

        std::vector < VkExtensionProperties > availableExtensions ( extensionCount );
        vkEnumerateDeviceExtensionProperties ( device , nullptr , & extensionCount , availableExtensions.data () );

        /// Формируем набор запрошенных расширений
        std::set < std::string > requiredExtensions ( Configuration::vulkan ().deviceExtension.begin () ,
                                                      Configuration::vulkan ().deviceExtension.end () );

        /// Удаляем из набора найденые расширения
        for ( const auto & extension : availableExtensions )
        {
                requiredExtensions.erase ( extension.extensionName );
        }

        /// Возвращаем "пуст ли после удаления найденных расширений набор"
        return requiredExtensions.empty ();
}

const PhysicalDevice::QueueFamilyIndices &
PhysicalDevice::getIndices () const
{
        return indices;
}

const VkPhysicalDevice &
PhysicalDevice::getPhysicalDevice () const
{
        return physicalDevice;
}

