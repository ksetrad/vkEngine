//
// Created by Владимир on 15.09.2020.
//

#ifndef ENGINE_STATES_IDLE_H
#define ENGINE_STATES_IDLE_H

#include "engine/states/state.h"

namespace engine
{
	class Idle
			: public State
	{
		public:
			explicit
			Idle ( Scene * scene );

			void
			mouseMoveEvent ( const glfw::MouseEvent &event ) override;

			void
			mousePressEvent ( const glfw::MouseEvent &event ) override;

			void
			mouseReleaseEvent ( const glfw::MouseEvent &event ) override;
	};
};
#endif //ENGINE_STATES_IDLE_H
