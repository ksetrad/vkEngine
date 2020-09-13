//
// Created by Владимир on 09.09.2020.
//

#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include <tools/vk/pipeLine.h>
#include <tools/vk/synchronization/fence.h>
#include <tools/vk/synchronization/semaphore.h>
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

            uint32_t
            getImage(vk::Semaphore* pWaitSemaphore);
        private:
            vk::Core * core;

            MainRenderPass * mainRenderPass;

            vk::PipeLine * mainPipeLine;

            CommandPool * commandPool;

            vk::DescriptorsPool * descriptorsPool;

            vk::FrameBuffer * frameBuffers;

            ModelFactory * modelFactory;

            Environment * environment;

            /// Набор глобальных буферов
            vk::UniformBufferSet * bufferSet;

            /// Заборы кадров буферизации
            std::vector < vk::Fence * > inFlightFences;
            /// Указатели на заборы кадров буферизации для используемых в данных момент изображений цепочки
            std::vector < vk::Fence * > imagesInFlight;

            /// Семафоры
            std::vector < vk::Semaphore * > renderFinishedSemaphores;

            std::vector < vk::Semaphore * > imageAvailableSemaphores;

            /// Максимальное число кадров в полете
            int frame_number { 3 };

            /// Номер текущего кадра
            int currentFrameId { 0 };
        };
}
#endif //ENGINE_CORE_H
