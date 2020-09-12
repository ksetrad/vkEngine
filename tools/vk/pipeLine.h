//
// Created by Владимир on 02.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_H
#define TOOLS_VK_PIPELINE_H

#include "tools/vk/logicalDevice.h"
#include "tools/vk/pipeLine/assemblyState.h"
#include "tools/vk/pipeLine/rasterizationState.h"
#include "tools/vk/pipeLine/shaderModule.h"
#include "tools/vk/pipeLine/blending.h"
#include "tools/vk/pipeLine/multisampling.h"
#include "tools/vk/pipeLine/pipeLineLayout.h"
#include "tools/vk/pipeLine/viewportstate.h"
#include "tools/vk/pipeLine/blending.h"
#include "tools/vk/pipeLine/vertexInputInfo.h"

namespace vk
{
    class PipeLine
        {
        public:
            /// Конструктор
            /// \param device логический интерфейс
            explicit
            PipeLine ( LogicalDevice * device );

            virtual ~PipeLine ();

            /// Установить шейдерные стадии
            /// \param stages стадии
            void
            setShaderStages ( std::vector < pipeline::ShaderModule * > stages );

            /// Инициализация
            /// \param renderPass Проход рендеринга
            void
            initialize ( VkRenderPass const & renderPass );

            /// Установить параметры смешивания цветов
            /// \param blending параметры
            void
            setBlending ( const pipeline::Blending & blending );

            /// Установить параметры макета дескрипторов конвеера
            /// \param pipeLineLayout параметры
            void
            setPipeLineLayout ( const pipeline::PipeLineLayout * pipeLineLayout );

            /// Установить параметры вывода вложений в конвеере
            /// \param viewPortState параметры
            void
            setViewPortState ( const pipeline::ViewPortState * viewPortState );

            /// Настроить мультисемплинг для конвеера
            /// \param multisampling параметры
            void
            setMultisampling ( const pipeline::Multisampling & multisampling );

            /// Установить параметры растеризации
            /// \param rasterizationState параметры
            void
            setRasterizationState ( const pipeline::RasterizationState & rasterizationState );

            /// Установить параметры формирования GPU примитивов
            /// \param assemblyState параметры
            void
            setAssemblyState ( const pipeline::AssemblyState & assemblyState );

        private:
            /// Дескриптор конвеера
            VkPipeline pipeLine;

            /// Интерфейс логического устройства
            LogicalDevice * device;

            /// Шейдерные модули
            std::vector < pipeline::ShaderModule * > stages;

            /// Параметры смешивания цветов
            pipeline::Blending blendingInfo { false };

            /// Параметры мультисэмплинга
            pipeline::Multisampling multisampling { false };

            /// Макет конвеера
            const pipeline::PipeLineLayout* layout;

            /// Макет конвеера
            const pipeline::ViewPortState* viewPortState;

            /// Растеризатор
            pipeline::RasterizationState rasterizationState {};

            /// Параметры входных вершин конвеера
            pipeline::VertexInputInfo vertexInfo{};

            /// Свойства сборки из вершин (точки/линии/треугольники)
            pipeline::AssemblyState assemblyState { pipeline::AssemblyState::TRIANGLES };
        };
}
#endif //TOOLS_VK_PIPELINE_H
