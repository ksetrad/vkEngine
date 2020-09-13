//
// Created by Владимир on 09.09.2020.
//

#ifndef TOOLS_VK_COMMON_VERTEX_H
#define TOOLS_VK_COMMON_VERTEX_H

#include <glm/glm.hpp>
#include <array>
#include <vulkan/vulkan.h>

namespace vk
{
    /// Структура вершины
    struct Vertex
        {
            /// Вершинная координата
            glm::vec3 p;

            /// Текстурная координата
            glm::vec2 t;

            /// Нормаль
            glm::vec3 n;

            /// Получить описание атрибутов в шейдере для входного буфера вершин
            /// \return Структура описание
            static std::array < VkVertexInputAttributeDescription , 3 >
            getAttributeDescriptions ()
            {
                    std::array < VkVertexInputAttributeDescription , 3 > attributeDescriptions { };

                    attributeDescriptions[ 0 ].binding = 0;
                    attributeDescriptions[ 0 ].location = 0;
                    attributeDescriptions[ 0 ].format = VK_FORMAT_R32G32B32_SFLOAT;
                    attributeDescriptions[ 0 ].offset = offsetof( Vertex , p );

                    attributeDescriptions[ 1 ].binding = 0;
                    attributeDescriptions[ 1 ].location = 1;
                    attributeDescriptions[ 1 ].format = VK_FORMAT_R32G32_SFLOAT;
                    attributeDescriptions[ 1 ].offset = offsetof( Vertex , t );

                    attributeDescriptions[ 2 ].binding = 0;
                    attributeDescriptions[ 2 ].location = 2;
                    attributeDescriptions[ 2 ].format = VK_FORMAT_R32G32B32_SFLOAT;
                    attributeDescriptions[ 2 ].offset = offsetof( Vertex , n );

                    return attributeDescriptions;
            }

            /// Получить описание привязки в шейдере для входного буфера вершин
            /// \return Структура описание
            static VkVertexInputBindingDescription getBindingDescription() {
                    VkVertexInputBindingDescription bindingDescription{};
                    /// Индекс привязки
                    bindingDescription.binding = 0;
                    /// Смещение между вершинами в массиве
                    bindingDescription.stride = sizeof(Vertex);
                    /// Признак вершинного буфера
                    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                    return bindingDescription;
            }
        };
}
#endif //TOOLS_VK_COMMON_VERTEX_H
