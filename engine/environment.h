//
// Created by Владимир on 12.09.2020.
//

#ifndef ENGINE_ENVIRONMENT_H
#define ENGINE_ENVIRONMENT_H

#include "engine/data/model.h"
#include <vector>

namespace engine
{
	struct Environment {
		virtual ~Environment ();

		std::vector< Model * > models;
	};
}// namespace engine
#endif//ENGINE_ENVIRONMENT_H
