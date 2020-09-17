//
// Created by Владимир on 12.09.2020.
//

#ifndef ENGINE_COMMON_UNIFORM_H
#define ENGINE_COMMON_UNIFORM_H

#include <glm/glm.hpp>

namespace engine
{
	struct Uniform
	{
		alignas ( 16 ) glm::mat4 model;
		alignas ( 16 ) glm::mat4 view;
		alignas ( 16 ) glm::mat4 proj;
	};
}// namespace engine
#endif//ENGINE_COMMON_UNIFORM_H
