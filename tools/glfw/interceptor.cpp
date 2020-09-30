//
// Created by Владимир on 14.09.2020.
//

#include "interceptor.h"
#include "handler.h"
#include <memory>

void
glfw::Interceptor::mouseButtonCallBack (
		GLFWwindow * window,
		int button,
		int action,
		int mods
)
{
	instance ()->handler->mouse_callBack ( window, button, action, mods );
}

void
glfw::Interceptor::initialize ( Handler * handler )
{
	instance ()->handler = handler;
}

glfw::Interceptor *
glfw::Interceptor::instance ()
{
	static std::unique_ptr <Interceptor> m_instance ( nullptr );
	if ( m_instance == nullptr )
	{
		m_instance = std::make_unique <Interceptor> ();
	}
	return m_instance.get ();
}

void
glfw::Interceptor::mouseMoveCallBack (
		GLFWwindow * window,
		double xpos,
		double ypos
)
{
	instance ()->handler->mouseMove ( window, xpos, ypos );
}

void
glfw::Interceptor::keyButtonCallBack (
		GLFWwindow * window,
		int key,
		int scancode,
		int action,
		int mods
)
{
	instance ()->handler->key_callBack ( window, key, scancode, action, mods );
}

void
glfw::Interceptor::scrollCallBack (
		GLFWwindow * window,
		double xoffset,
		double yoffset
)
{
	instance ()->handler->scroll_callBack ( window, xoffset, yoffset );
}
