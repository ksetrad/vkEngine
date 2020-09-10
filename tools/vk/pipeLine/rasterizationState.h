//
// Created by Владимир on 09.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_RASTERIZATIONSTATE_H
#define TOOLS_VK_PIPELINE_RASTERIZATIONSTATE_H

#include <vulkan/vulkan.h>

namespace vk::pipeline
{
    /// Функционал параметров вывода кадра в конвеере
    class RasterizationState
        {
        public:
            /// Конструктор
            /// \param swapChain цепочка смены кадров
            explicit
            RasterizationState();

            /// Получить указатель на структуру параметров
            /// \return указатель
            VkPipelineRasterizationStateCreateInfo  *
            getInfo ();

        private:
            /// Структура параметров
            VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo{};
        };
}
#endif //TOOLS_VK_PIPELINE_RASTERIZATIONSTATE_H
