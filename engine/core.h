//
// Created by Владимир on 09.09.2020.
//

#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include <tools/vk/pipeLine.h>
#include "tools/vk/core.h"
#include "tools/vk/frameBuffer.h"
#include "mainRenderPass.h"
#include "commandPool.h"

namespace engine
{
    class Core
        {
        public:
            Core ();

            virtual ~Core ();

            void
            mainLoop();
        private:
            vk::Core* core;

            MainRenderPass* mainRenderPass;

            vk::PipeLine* mainPipeLine;

            CommandPool* commandPool;

            vk::FrameBuffer* frameBuffers;
        };
}
#endif //ENGINE_CORE_H
