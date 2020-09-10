//
// Created by Владимир on 06.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_ASSEMBLYSTATE_H
#define TOOLS_VK_PIPELINE_ASSEMBLYSTATE_H

#include <vulkan/vulkan.h>

namespace vk::pipeline
{
    /// Фукнционал преобразования вершин в графические примитивы
    class AssemblyState
        {
        public:
            /// Типы примитивов
            enum Types{
                /// Точки
                POINTS,
                /// Линии
                LINES,
                /// Треугольник
                TRIANGLES
            };

            /// Конструктор
            /// \param types тип преобразования вершин
            explicit
            AssemblyState (
                    const Types & types
                     );

            /// Получить указатель на структуру
            /// \return указатель
            VkPipelineInputAssemblyStateCreateInfo*
            getInfo();
        private:
            /// Структура с инофрмацией о функционале
            VkPipelineInputAssemblyStateCreateInfo createInfo;
        };
}
#endif //TOOLS_VK_PIPELINE_ASSEMBLYSTATE_H
