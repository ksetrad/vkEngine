//
// Created by Владимир on 02.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_SHADER_H
#define TOOLS_VK_PIPELINE_SHADER_H

#include <string>
#include <vulkan/vulkan.h>
#include <tools/vk/logicalDevice.h>

namespace vk::pipeline
{
    /// Класс шейдерного модуль
    class ShaderModule
        {
        public:
            /// Типы шейдерных модулей
            enum Types
                {
                    /// Вершинный
                    Vertex ,
                    /// Геометрический
                    Geometry ,
                    /// Фрагментный
                    Fragment
                };

            /// Конструктор
            /// \param filename имя файла
            /// \param device логический интерфейс
            /// \param type тип шейдера
            explicit
            ShaderModule (
                    const std::string & filename ,
                    LogicalDevice * device ,
                    const Types & type
                         );

            /// Получить структуру описания шейдерной стадии
            /// \return Дескриптор
            [[nodiscard]] const VkPipelineShaderStageCreateInfo &
            getShaderStage () const;

            virtual ~ShaderModule ();

        private:
            /// Шейдерный модуль
            VkShaderModule shaderModule { VK_NULL_HANDLE };

            /// Описание шейдерной стадии
            VkPipelineShaderStageCreateInfo shaderStage { };

            /// Указатель на логический интерфейс
            LogicalDevice * device;
        };
}
#endif //TOOLS_VK_PIPELINE_SHADER_H
