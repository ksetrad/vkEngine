//
// Created by Владимир on 06.09.2020.
//

#ifndef TOOLS_VK_RENDERPASS_H
#define TOOLS_VK_RENDERPASS_H

#include <map>
#include <vector>
#include <vulkan/vulkan.h>

#include "tools/vk/core.h"

namespace vk
{
    /// Проход рендеринга
    class RenderPass
        {
        public:
            /// Конструктор
            /// \param core ядро Vulkan
            explicit
            RenderPass (
                    Core * core
                       );

            virtual ~RenderPass ();

            /// Получить дескриптор прохода рендеринга
            /// \return Дескриптор
            [[nodiscard]] const VkRenderPass &
            getRenderPass () const;

        protected:
            /// Дескриптор
            VkRenderPass renderPass { VK_NULL_HANDLE };

            /// Логический интерфейс GPU
            LogicalDevice * device;
        };
}

#endif //TOOLS_VK_RENDERPASS_H
