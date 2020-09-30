//
// Created by Владимир on 14.09.2020.
//

#ifndef TOOLS_GLFW_INTERCEPTOR_H
#define TOOLS_GLFW_INTERCEPTOR_H

#include <GLFW/glfw3.h>


namespace glfw
{
	class Handler;

	class Interceptor
	{
		public:
			static void
			mouseButtonCallBack (
					GLFWwindow * window,
					int button,
					int action,
					int mods
			);

			static void
			keyButtonCallBack (
					GLFWwindow * window,
					int key,
					int scancode,
					int action,
					int mods
			);

			static void
			mouseMoveCallBack (
					GLFWwindow * window,
					double xpos,
					double ypos
			);

			static void
			scrollCallBack (
					GLFWwindow * window,
					double xoffset,
					double yoffset
			);

			static Interceptor *
			instance ();

			static void
			initialize ( Handler * handler );

		private:
			Handler * handler;
	};
}// namespace glfw
#endif//TOOLS_GLFW_INTERCEPTOR_H
