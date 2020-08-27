//
// Created by Владимир on 15.08.2020.
//
#include <cstring>
#include <utility>
#include <tools/logger.h>
#include <tools/exceptions.h>

#include "tools/vk/validationLayers.h"

using namespace vk;

VkBool32
ValidationLayers::debugCallback (
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity ,
        VkDebugUtilsMessageTypeFlagsEXT messageType ,
        const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData ,
        void * pUserData
                                )
{
        if ( ( messageType &
               ( VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT ) ) )
        {
                Logger::message ( Logger::warning ,Logger::Alias ( "FULL" ), pCallbackData->pMessage );
        }
        if ( messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT )
        {
                Logger::message ( Logger::warning ,Logger::Alias ( "FULL" ), pCallbackData->pMessage );
        }
        else if ( messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT )
        {
                Logger::message ( Logger::error , pCallbackData->pMessage );
        }
        else
        {
                Logger::message ( Logger::info ,Logger::Alias ( "FULL" ), pCallbackData->pMessage );
        }

        return VK_FALSE;
}

const std::vector < const char * > &
ValidationLayers::getValidationLayers () const
{
        return validationLayers;
}

bool
ValidationLayers::checkLayers ()
{
        /// Вычисляем количество доступных в системе слоев проверки
        uint32_t layerCount;
        /// Функция вычисления
        vkEnumerateInstanceLayerProperties ( & layerCount , nullptr );
        /// Формируем массив из доступных слоев проверки
        std::vector < VkLayerProperties > availableLayers ( layerCount );
        vkEnumerateInstanceLayerProperties ( & layerCount , availableLayers.data () );

        /// Проверям наличие каждого из запрошенных нами уровней, в доступных слоях проверки
        for ( const char * layerName : validationLayers )
        {
                bool layerFound = false;

                for ( const auto & layerProperties : availableLayers )
                {
                        if ( strcmp ( layerName , layerProperties.layerName ) == 0 )
                        {
                                /// Если уровень найден, переходим к поиску следующего уровня
                                layerFound = true;
                                break;
                        }
                }

                if ( !layerFound )
                {
                        /// Если уровень не найден, выходим из функции с false
                        return false;
                }
        }
        /// Все нашли - успех
        return true;
}

VkDebugUtilsMessengerCreateInfoEXT
ValidationLayers::constructDebugInfo ()
{
        VkDebugUtilsMessengerCreateInfoEXT createInfo = { };
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity =
                /// Все уровни диагностических сообщений
                /// Подровный вывод сообщений загрузчика, слоев, драйверов
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                /// Иноформационные сообщения
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                /// Баги и предупреждения
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                /// Ошибки
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType =
                /// Типы событий при которых вызывается отладочный мессенджер (опять же все события)
                /// События не связанные со спецификацией
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                /// Событие приводящее к недопустимому поведению
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                /// Потенциально не приемлимое использование Vulkan
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        return createInfo;
}

ValidationLayers::ValidationLayers ( const std::vector < std::string > & validationLayersNames )
{
        /// Выделяем память под имена слоев
        validationLayers.resize ( validationLayersNames.size () );
        /// Заполняем массив имен
        for ( unsigned int i = 0 ;
              i < validationLayers.size () ;
              i++ )
        {
                validationLayers[ i ] = validationLayersNames[ i ].c_str ();
        }
        /// Проверям наличие запрошеных слоев
        if ( !checkLayers () )
        {
                throw vulkan_exception ( "validation layers requested, but not available!" );
        }
}

VkResult
ValidationLayers::initialize ( VkInstance * pinstance )
{
        /// Сохраняем указатель на Vulkan
        instance = pinstance;
        /// Формируем инициализационную структуру мессенджера
        auto pCreateInfo = constructDebugInfo ();
        /// Ищем функцкию создания объекта мессенджера отладочных сообщений в дополнении
        auto func = ( PFN_vkCreateDebugUtilsMessengerEXT ) vkGetInstanceProcAddr ( * instance ,
                                                                                   "vkCreateDebugUtilsMessengerEXT" );
        if ( func != nullptr )
        {
                /// Если функция найдера то возвращаем результат её вызова
                return func ( * instance , & pCreateInfo , nullptr , & debugMessenger );
        }
        else
        {
                /// Иначе ошибка
                return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
}

ValidationLayers::~ValidationLayers ()
{
        /// Получаем функцию для разрушения мессендежра
        auto func = ( PFN_vkDestroyDebugUtilsMessengerEXT ) vkGetInstanceProcAddr ( * instance ,
                                                                                    "vkDestroyDebugUtilsMessengerEXT" );
        if ( func != nullptr )
        {
                /// Если функция найдена - вызываем её
                func ( * instance , debugMessenger , nullptr );
        }

}

