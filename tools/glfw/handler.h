//
// Created by Владимир on 14.09.2020.
//

#ifndef TOOLS_GLFW_HANDLER_H
#define TOOLS_GLFW_HANDLER_H

#include <string>
#include "event.h"

namespace glfw
{

	class Handler
	{
		public:
			Handler (
					int width,
					int height,
					const std::string &title
			);


			void
			mousePress (
					GLFWwindow *window,
					int button,
					int action,
					int mods
			);

			void
			mouseMove (
					GLFWwindow *window,
					double xpos,
					double ypos
			);

		protected:
			virtual void
			mouseMoveEvent ( const MouseEvent &event )
			{
			}

			virtual void
			mousePressEvent ( const MouseEvent &event )
			{
			}

			virtual void
			mouseReleaseEvent ( const MouseEvent &event )
			{
			}

			virtual void
			mouseWheelEvent ( const MouseEvent &event )
			{
			}

			GLFWwindow *m_window;

		private:
			glm::vec2 currentPos;
	};
}// namespace glfw
#endif//TOOLS_GLFW_HANDLER_H
