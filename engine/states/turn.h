//
// Created by Владимир on 15.09.2020.
//

#ifndef ENGINE_STATES_TURN_H
#define ENGINE_STATES_TURN_H

#include "state.h"

namespace engine
{
	class Turn
			: public State
	{
		public:
			explicit
			Turn ( Scene * scene );

			void
			mouseMoveEvent ( const glfw::MouseEvent & event ) override;

			void
			mousePressEvent ( const glfw::MouseEvent & event ) override;

			void
			mouseReleaseEvent ( const glfw::MouseEvent & event ) override;

			void
			switchMouseEvent (
					const glfw::MouseEvent & event,
					const StateType & root
			) override;

		private:
			glm::vec2 prevPos;
	};
}
#endif //ENGINE_STATES_TURN_H
