//
// Created by Владимир on 26.08.2020.
//

#ifndef TOOLS_VK_CORE_H
#define TOOLS_VK_CORE_H

#include "tools/vk/instance.h"
#include "tools/vk/logicalDevice.h"
#include "tools/vk/physicalDevice.h"
#include "tools/vk/swapChain.h"

namespace vk
{
    /// Ядро Vulkan
    class Core
        {
        public:
            /// Конструктор
            Core ();

            /// Деструктор
            ~Core ();

            /// Получить логический интерфейс GPU
            /// \return указатель на логический интерфейс
            [[nodiscard]] LogicalDevice *
            getLogicalDevice () const;

            /// Получить физический интерфейс GPU
            /// \return указатель на физический интерфейс
            [[nodiscard]] PhysicalDevice *
            getPhysicalDevice () const;

            /// Получить цепочку смены кадров
            /// \return указатель на цепочку смены кадров
            [[nodiscard]] SwapChain *
            getSwapChain () const;

            /// Получить окно вывода
            /// \return окно
            [[nodiscard]] GLFWwindow *
            getWindow () const;

        private:
            /// Окно
            GLFWwindow * window;

            /// Экземпляр Vulkan
            Instance * instance;
            
            /// Логический интерфейс GPU
            LogicalDevice * logicalDevice;

            /// Физический интерфейс GPU
            PhysicalDevice * physicalDevice;

            /// Цепочка смены кадров
            SwapChain* swapChain;
        };
}
#endif //TOOLS_VK_CORE_H
