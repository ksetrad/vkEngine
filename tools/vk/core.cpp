//
// Created by Владимир on 26.08.2020.
//

#include <tools/configuration.h>
#include "core.h"

using namespace vk;

Core::Core ()
{
        /// Инициализируем GLFW
        glfwInit ();
        /// Отключаем поддержку OpenGL (GLFW разработана для OpenGL)
        glfwWindowHint ( GLFW_CLIENT_API , GLFW_NO_API );
        /// Отключчаем возможность изменения размера окна
        glfwWindowHint ( GLFW_RESIZABLE , GLFW_FALSE );
        /// Инициализируем GLFW
        glfwInit ();
        /// Создаем окно
        window = glfwCreateWindow ( Configuration::display ().resolution.width ,
                                    Configuration::display ().resolution.height ,
                                    Configuration::vulkan ().appName.c_str () , nullptr , nullptr );

        /// Конструируем экземпляр Vulkan
        instance = new Instance ( window );

        /// Конструируем и настраиваем объект используемого GPU
        physicalDevice = new PhysicalDevice ( instance );

        /// Конструируем логический интерфейс GPU
        logicalDevice = new LogicalDevice ( instance , physicalDevice );


}

Core::~Core ()
{
        /// Уничтожаем экземпляр логического устройства
        delete logicalDevice;
        /// Уничтожаем экземпляр физического устройство
        delete physicalDevice;
        /// Уничтожаем экземпляр Vulkan
        delete instance;
        /// Разрушаем окно
        glfwDestroyWindow ( window );
}

