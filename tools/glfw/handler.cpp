//
// Created by Владимир on 14.09.2020.
//

#include <GLFW/glfw3.h>

#include <string>

#include "tools/glfw/handler.h"
#include "tools/glfw/interceptor.h"

using namespace glfw;

Handler::Handler (
		int width,
		int height,
		const std::string &title
)
{
	/// Инициализируем GLFW
	glfwInit ();
	/// Отключаем поддержку OpenGL (GLFW разработана для OpenGL)
	glfwWindowHint ( GLFW_CLIENT_API, GLFW_NO_API );
	/// Отключчаем возможность изменения размера окна
	glfwWindowHint ( GLFW_RESIZABLE, GLFW_FALSE );
	/// Создаем окно
	m_window = glfwCreateWindow ( width, height, title.c_str (), nullptr, nullptr );
	Interceptor::initialize ( this );
	glfwSetMouseButtonCallback ( m_window, Interceptor::mouseButtonCallBack );
	glfwSetCursorPosCallback ( m_window, Interceptor::mouseMove );
}

void
Handler::mousePress (
		GLFWwindow *window,
		int button,
		int action,
		int mods
)
{
	MouseEvent::MouseButtons button_type;
	if ( button == GLFW_MOUSE_BUTTON_1 )
	{
		button_type = MouseEvent::MouseButtons::MOUSE_LEFT_BUTTON;
	}
	else if ( button == GLFW_MOUSE_BUTTON_2 )
	{
		button_type = MouseEvent::MouseButtons::MOUSE_RIGHT_BUTTON;
	}
	else if ( button == GLFW_MOUSE_BUTTON_3 )
	{
		button_type = MouseEvent::MouseButtons::MOUSE_WHEEL;
	}
	else
	{
		button_type = MouseEvent::NOBUTTON;
	}
	Event::Mods mode;
	if ( mods == GLFW_MOD_SHIFT )
	{
		mode = Event::SHIFT;
	}
	else if ( mods == GLFW_MOD_CONTROL )
	{
		mode = Event::CTRL;
	}
	else if ( mods == GLFW_MOD_ALT )
	{
		mode = Event::ALT;
	}
	else
	{
		mode = Event::NOMODE;
	}

	if ( action == GLFW_PRESS )
	{
		mousePressEvent ( MouseEvent ( button_type, currentPos, mode ) );
	}
	else if ( action == GLFW_RELEASE )
	{
		mouseReleaseEvent ( MouseEvent ( button_type, currentPos, mode ) );
	}
}

void
Handler::mouseMove (
		GLFWwindow *window,
		double xpos,
		double ypos
)
{
	currentPos = { xpos, ypos };
	mouseMoveEvent ( MouseEvent ( MouseEvent::NOBUTTON, currentPos, MouseEvent::NOMODE ) );
}
