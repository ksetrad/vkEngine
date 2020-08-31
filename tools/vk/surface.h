//
// Created by Владимир on 31.08.2020.
//

#ifndef TOOLS_VK_SURFACE_H
#define TOOLS_VK_SURFACE_H

#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>

namespace vk
{
    class Instance;
    /// Поверхность отображения
    class Surface
        {

        public:
            /// Конструктор
            /// \param instance Экземпляр Vulkan
            /// \param window Окно вывода
            Surface ( Instance* instance, GLFWwindow * window );

            /// Деструктор
            virtual ~Surface ();

            /// Проверить подходит ли очередь физического устройства для отправки команд отображения на данной поверхности
            /// \param physicalDevice Физическое устройство
            /// \param queueId идентификатор очереди
            /// \return Результат проверки
            bool
            checkPresent (
                    const VkPhysicalDevice & physicalDevice ,
                    const int & queueId
                         );

        private:
            /// Экземпляр Vulkan
            Instance* instance;

            /// Поверхность отображения
            VkSurfaceKHR surface;

        };
}
#endif //TOOLS_VK_SURFACE_H
