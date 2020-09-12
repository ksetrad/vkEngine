//
// Created by Владимир on 10.09.2020.
//

#ifndef ENGINE_COMMANDPOOL_H
#define ENGINE_COMMANDPOOL_H


#include "tools/vk/commandPool.h"
#include "tools/vk/core.h"

namespace engine
{
    class CommandPool
            : public vk::CommandPool
        {
        public:
            explicit
            CommandPool ( vk::Core * core );
        };
}
#endif //ENGINE_COMMANDPOOL_H
