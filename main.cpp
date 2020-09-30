//
// Created by Владимир on 26.08.2020.
//

#include "engine/scene.h"
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
	engine::Scene core;
	core.mainLoop ();
	return 0;
}