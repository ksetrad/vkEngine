//
// Created by Владимир on 09.09.2020.
//

#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include <tools/vk/pipeLine.h>
#include "tools/vk/core.h"
#include "tools/vk/frameBuffer.h"
#include "tools/vk/uniformBufferSet.h"
#include "mainRenderPass.h"
#include "commandPool.h"
#include "modelFactory.h"

namespace engine
{
    class Core
        {
        public:
            Core ();

            virtual ~Core ();

            void
            mainLoop ();

        private:
            vk::Core * core;

            MainRenderPass * mainRenderPass;

            vk::PipeLine * mainPipeLine;

            CommandPool * commandPool;
            vk::DescriptorsPool * descriptorsPool;

            vk::FrameBuffer * frameBuffers;

            ModelFactory * modelFactory;

            Environment* environment;

            /// Набор глобальных буферов
            vk::UniformBufferSet * bufferSet;
        };
}
#endif //ENGINE_CORE_H
