//
// Created by Владимир on 08.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_VIEWPORTSTATE_H
#define TOOLS_VK_PIPELINE_VIEWPORTSTATE_H

#include <vulkan/vulkan.h>
#include <tools/vk/swapChain.h>

namespace vk::pipeline
{
    /// Функционал параметров вывода кадра в конвеере
    class ViewPortState
        {
        public:
            /// Конструктор
            /// \param swapChain цепочка смены кадров
            explicit
            ViewPortState(SwapChain* swapChain);

            /// Получить указатель на структуру параметров
            /// \return указатель
            [[nodiscard]]
            const VkPipelineViewportStateCreateInfo *
            getInfo () const;

        private:
            VkViewport viewport{};
            VkRect2D scissor{};
            /// Структура параметров
            VkPipelineViewportStateCreateInfo viewportStateCreateInfo{};
        };
}
#endif //TOOLS_VK_PIPELINE_VIEWPORTSTATE_H
