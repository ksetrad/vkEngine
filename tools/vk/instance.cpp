//
// Created by Владимир on 26.08.2020.
//

#include "tools/vk/instance.h"
#include "tools/configuration.h"

using namespace vk;

Instance::Instance ( GLFWwindow * window )
{
        /// Инофрмация по приложению
        VkApplicationInfo appInfo { };
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        /// Название и версия приложения
        appInfo.pApplicationName = Configuration::vulkan ().appName.c_str ();
        appInfo.applicationVersion = VK_MAKE_VERSION( 1 , 0 , 0 );
        /// Название и версия движка
        appInfo.pEngineName = Configuration::vulkan ().engineName.c_str ();
        appInfo.engineVersion = VK_MAKE_VERSION( 1 , 0 , 0 );
        /// Версия API Vulkan (единственный полезный пункт)
        appInfo.apiVersion = VK_API_VERSION_1_0;

        /// Настраиваем структуру для инициализации Vulkan
        VkInstanceCreateInfo createInfo { };
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        /// Устанавливаем параметры приложения
        createInfo.pApplicationInfo = & appInfo;

        /// Необходимые расширения для GLFW
        uint32_t glfwExtensionCount = 0;
        const char ** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions ( & glfwExtensionCount );
        /// Формируем массив расширений
        std::vector < const char * > extensions ( glfwExtensions , glfwExtensions + glfwExtensionCount );
#ifdef VULKAN_DEBUG
        /// Если режим DEBUG добавляем соответствующее расширение
        extensions.push_back ( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );
#endif
        /// Устанавливаем количество полученных расширений
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size ());
        /// И значения
        createInfo.ppEnabledExtensionNames = extensions.data ();

#ifdef VULKAN_DEBUG

        validationLayers = new ValidationLayers ( Configuration::vulkan ().validationLayers );
        /// Число уровней проверки
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers->getValidationLayers ().size ());
        /// Массив значений
        createInfo.ppEnabledLayerNames = validationLayers->getValidationLayers ().data ();

        /// Формируем структуру с информациией по подробности отладочных сообщений
        auto debugInfo = ValidationLayers::constructDebugInfo ();
        createInfo.pNext = & debugInfo;
#else
        /// Если DEBUG отключен - число уровней проверки 0
        createInfo.enabledLayerCount = 0;
#endif
        /// Инициализируем Vulkan
        if ( vkCreateInstance ( & createInfo , nullptr , & instance ) != VK_SUCCESS )
        {
                throw vulkan_exception( "failed to create instance!" );
        }

#ifdef VULKAN_DEBUG
        /// Инициализируем слои проверки
        if ( validationLayers->initialize ( & instance ) != VK_SUCCESS )
        {
                throw vulkan_exception( "failed to set up debug messenger!" );
        }
#endif
        /// Создаем поверхность отрисовки
        surface = new Surface ( this , window );
}

Instance::~Instance ()
{
        /// Разрушаем поверхность отрисовки
        delete surface;
#ifdef VULKAN_DEBUG
        /// Уничтожаем слои проверки
        delete validationLayers;
#endif
        /// Уничтожаем экземпляр Vulkan
        vkDestroyInstance ( instance , nullptr );
}

VkInstance
Instance::getInstance () const
{
        return instance;
}

Surface *
Instance::getSurface () const
{
        return surface;
}

