//
// Created by Владимир on 26.08.2020.
//

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "tools/exceptions.h"
#include "validationLayers.h"

#ifndef TOOLS_VK_INSTANCE_H
#define TOOLS_VK_INSTANCE_H
namespace vk
{
    class Instance
        {
        public:
            /// Конструктор
            Instance ();

            /// Деструктор
            ~Instance ();

            /// Получить указатель на экземпляр Vulkan
            /// \return Указатель
            VkInstance
            getInstance ();

        private:
            /// Экземпляр Vulkan
            VkInstance instance;

#ifdef VULKAN_DEBUG

            /// Слои проверки
            ValidationLayers * validationLayers;

#endif
        };
}
#endif //TOOLS_VK_INSTANCE_H
