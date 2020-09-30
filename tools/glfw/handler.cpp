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
		const std::string & title
)
{
	/// Инициализируем GLFW
	glfwInit ();
	/// Отключаем поддержку OpenGL (GLFW разработана для OpenGL)
	glfwWindowHint ( GLFW_CLIENT_API, GLFW_NO_API );
	/// Отключчаем возможность изменения размера окна
	glfwWindowHint ( GLFW_RESIZABLE, GLFW_FALSE );
	/// Создаем окно
	glfwWindowHint ( GLFW_DOUBLEBUFFER, GL_FALSE );
//	glfwSwapInterval( 0 );
	m_window = glfwCreateWindow ( width, height, title.c_str (), nullptr, nullptr );
	Interceptor::initialize ( this );
	glfwSetMouseButtonCallback ( m_window, Interceptor::mouseButtonCallBack );
	glfwSetCursorPosCallback ( m_window, Interceptor::mouseMoveCallBack );
	glfwSetKeyCallback ( m_window, Interceptor::keyButtonCallBack );
	glfwSetScrollCallback ( m_window, Interceptor::scrollCallBack );
}

void
Handler::mouse_callBack (
		GLFWwindow * window,
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
		GLFWwindow * window,
		double xpos,
		double ypos
)
{
	currentPos = { xpos, ypos };
	mouseMoveEvent ( MouseEvent ( MouseEvent::NOBUTTON, currentPos, MouseEvent::NOMODE ) );
}

void
Handler::key_callBack (
		GLFWwindow * window,
		int key,
		int scancode,
		int action,
		int mods
)
{
	KeyEvent::KeyButtons button_type;
	switch ( key )
	{
		case GLFW_KEY_0:
			button_type = KeyEvent::KEY_0;
			break;
		case GLFW_KEY_1:
			button_type = KeyEvent::KEY_1;
			break;
		case GLFW_KEY_2:
			button_type = KeyEvent::KEY_2;
			break;
		case GLFW_KEY_3:
			button_type = KeyEvent::KEY_3;
			break;
		case GLFW_KEY_4:
			button_type = KeyEvent::KEY_4;
			break;
		case GLFW_KEY_5:
			button_type = KeyEvent::KEY_5;
			break;
		case GLFW_KEY_6:
			button_type = KeyEvent::KEY_6;
			break;
		case GLFW_KEY_7:
			button_type = KeyEvent::KEY_7;
			break;
		case GLFW_KEY_8:
			button_type = KeyEvent::KEY_8;
			break;
		case GLFW_KEY_9:
			button_type = KeyEvent::KEY_9;
			break;
		case GLFW_KEY_A:
			button_type = KeyEvent::KEY_A;
			break;
		case GLFW_KEY_B:
			button_type = KeyEvent::KEY_B;
			break;
		case GLFW_KEY_C:
			button_type = KeyEvent::KEY_C;
			break;
		case GLFW_KEY_D:
			button_type = KeyEvent::KEY_D;
			break;
		case GLFW_KEY_E:
			button_type = KeyEvent::KEY_E;
			break;
		case GLFW_KEY_F:
			button_type = KeyEvent::KEY_F;
			break;
		case GLFW_KEY_G:
			button_type = KeyEvent::KEY_G;
			break;
		case GLFW_KEY_I:
			button_type = KeyEvent::KEY_I;
			break;
		case GLFW_KEY_J:
			button_type = KeyEvent::KEY_J;
			break;
		case GLFW_KEY_H:
			button_type = KeyEvent::KEY_H;
			break;
		case GLFW_KEY_K:
			button_type = KeyEvent::KEY_K;
			break;
		case GLFW_KEY_L:
			button_type = KeyEvent::KEY_L;
			break;
		case GLFW_KEY_M:
			button_type = KeyEvent::KEY_M;
			break;
		case GLFW_KEY_N:
			button_type = KeyEvent::KEY_N;
			break;
		case GLFW_KEY_O:
			button_type = KeyEvent::KEY_O;
			break;
		case GLFW_KEY_P:
			button_type = KeyEvent::KEY_P;
			break;
		case GLFW_KEY_Q:
			button_type = KeyEvent::KEY_Q;
			break;
		case GLFW_KEY_R:
			button_type = KeyEvent::KEY_R;
			break;
		case GLFW_KEY_S:
			button_type = KeyEvent::KEY_S;
			break;
		case GLFW_KEY_T:
			button_type = KeyEvent::KEY_T;
			break;
		case GLFW_KEY_U:
			button_type = KeyEvent::KEY_U;
			break;
		case GLFW_KEY_V:
			button_type = KeyEvent::KEY_V;
			break;
		case GLFW_KEY_W:
			button_type = KeyEvent::KEY_W;
			break;
		case GLFW_KEY_X:
			button_type = KeyEvent::KEY_X;
			break;
		case GLFW_KEY_Y:
			button_type = KeyEvent::KEY_Y;
			break;
		case GLFW_KEY_Z:
			button_type = KeyEvent::KEY_Z;
			break;
		case GLFW_KEY_ESCAPE:
			button_type = KeyEvent::KEY_ESC;
			break;
		case GLFW_KEY_SPACE:
			button_type = KeyEvent::KEY_SPACEBAR;
			break;
		case GLFW_KEY_ENTER:
			button_type = KeyEvent::KEY_ENTER;
			break;
		case GLFW_KEY_UP:
			button_type = KeyEvent::KEY_UP;
			break;
		case GLFW_KEY_DOWN:
			button_type = KeyEvent::KEY_DOWN;
			break;
		case GLFW_KEY_LEFT:
			button_type = KeyEvent::KEY_LEFT;
			break;
		case GLFW_KEY_RIGHT:
			button_type = KeyEvent::KEY_RIGHT;
			break;
		case GLFW_KEY_TAB:
			button_type = KeyEvent::KEY_TAB;
			break;
		case GLFW_KEY_COMMA:
			button_type = KeyEvent::KEY_6;
			break;
		default:
			button_type = KeyEvent::NOBUTTON;

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
		keyPressEvent ( KeyEvent ( button_type, mode ) );
	}
	else if ( action == GLFW_RELEASE )
	{
		keyReleaseEvent ( KeyEvent ( button_type, mode ) );
	}
	else if ( action == GLFW_REPEAT )
	{
		keyRepeatEvent ( KeyEvent ( button_type, mode ) );
	}
}

void
Handler::scroll_callBack (
		GLFWwindow * window,
		double xoffset,
		double yoffset
)
{
	mouseWheelEvent ( { yoffset, Event::NOMODE } );
}
