//
// Created by Владимир on 12.09.2020.
//

#ifndef ENGINE_MODELFACTORY_H
#define ENGINE_MODELFACTORY_H

#include <tools/vk/commandsPool.h>
#include <engine/data/model.h>

namespace engine
{
	class ModelFactory
	{
		public:

			ModelFactory (
					vk::Core *core,
					vk::CommandPool *commandPool
			);

			Model *
			openModel ( const std::string &path );

		private:
			vk::Core *core;
			vk::CommandPool *commandPool;
	};
}
#endif //ENGINE_MODELFACTORY_H
