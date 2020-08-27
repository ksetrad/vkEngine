//
// Created by Владимир on 26.08.2020.
//

#include <tools/logger.h>
#include "tools/vk/core.h"

int
main (
        int argc ,
        char ** argv
     )
{
#ifdef VULKAN_DEBUG
        Logger::addComponent( "FULL", "FULL", Logger::info, true);
        Logger::setVerbosity(Logger::error);
#endif
        vk::Core core;
        return 0;
}