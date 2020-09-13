//
// Created by Владимир on 10.09.2020.
//

#ifndef ENGINE_COMMANDPOOL_H
#define ENGINE_COMMANDPOOL_H


#include <tools/vk/pipeLine.h>
#include "tools/vk/commandsPool.h"
#include "tools/vk/core.h"
#include "environment.h"

namespace engine
{
    class CommandPool
            : public vk::CommandPool
        {
        public:

            CommandPool (
                    vk::Core * core ,
                    vk::PipeLine * pipeLine ,
                    Environment * environment
                        );

            void
            setCommandBufferContent ( const VkCommandBuffer & commandBuffer, const VkDescriptorSet * descriptorSet ) override;

        private:
            void
            bindBuffer (
                    const vk::BufferObject & buffer ,
                    VkCommandBuffer const & commandBuffer
                       );

            vk::PipeLine * pipeLine;

            Environment * environment;
        };
}
#endif //ENGINE_COMMANDPOOL_H
