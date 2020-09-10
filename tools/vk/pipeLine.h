//
// Created by Владимир on 02.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_H
#define TOOLS_VK_PIPELINE_H

#include <tools/vk/pipeLine/assemblyState.h>
#include <tools/vk/pipeLine/rasterizationState.h>
#include "tools/vk/logicalDevice.h"
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
            initialize (VkRenderPass renderPass);

            void
            setBlending ( const pipeline::Blending & blending );

            void
            setPipeLineLayout ( const pipeline::PipeLineLayout * pipeLineLayout );

            void
            setViewPortState ( const pipeline::ViewPortState * viewPortState );

            void
            setMultisampling ( const pipeline::Multisampling & multisampling );

            void
            setRasterizationState ( const pipeline::RasterizationState & rasterizationState );

            void
            setAssemblyState ( const pipeline::AssemblyState & assemblyState );

        private:
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

            pipeline::VertexInputInfo vertexInfo{};

            /// Свойства сборки из вершин (точки/линии/треугольники)
            pipeline::AssemblyState assemblyState { pipeline::AssemblyState::TRIANGLES };
        };
}
#endif //TOOLS_VK_PIPELINE_H
