//
// Created by Владимир on 26.08.2020.
//

#include "engine/core.h"
#include <tools/logger.h>

int
main (
        int argc,
        char **argv )
{
#ifdef VULKAN_DEBUG
	Logger::addComponent ( "FULL", "FULL", Logger::info, true );
	Logger::setVerbosity ( Logger::error );
#endif
	engine::Core core;
	core.mainLoop ();
	return 0;
}