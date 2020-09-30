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
	m_window = glfwCreateWindow ( width, height, title.c_str (), nullptr, nullptr );
	/// Активируем перехватчик как активный
	makeCurrent();
}

void
Handler::mouse_callBack (
		int button,
		int action,
		int mods
)
{
	/// Определяем нажатую клавишу
	MouseEvent::MouseButtons button_type;
	switch ( button )
	{
		case GLFW_MOUSE_BUTTON_1:
			button_type = MouseEvent::MouseButtons::MOUSE_LEFT_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_2:
			button_type = MouseEvent::MouseButtons::MOUSE_RIGHT_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_3:
			button_type = MouseEvent::MouseButtons::MOUSE_WHEEL;
			break;
		case GLFW_MOUSE_BUTTON_4:
			button_type = MouseEvent::MouseButtons::MOUSE_BUTTON4;
			break;
		case GLFW_MOUSE_BUTTON_5:
			button_type = MouseEvent::MouseButtons::MOUSE_BUTTON5;
			break;
		case GLFW_MOUSE_BUTTON_6:
			button_type = MouseEvent::MouseButtons::MOUSE_BUTTON6;
			break;
		case GLFW_MOUSE_BUTTON_7:
			button_type = MouseEvent::MouseButtons::MOUSE_BUTTON7;
			break;
		case GLFW_MOUSE_BUTTON_8:
			button_type = MouseEvent::MouseButtons::MOUSE_BUTTON8;
			break;
		default:
			button_type = MouseEvent::NOBUTTON;
	}
	/// Определяем мод
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

	/// Определяем тип события и вызываем соответствующую функцию действия
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
		double xpos,
		double ypos
)
{
	/// Текущая позиция мыши запоминается при любом смещении
	currentPos = { xpos, ypos };
	mouseMoveEvent ( MouseEvent ( MouseEvent::NOBUTTON, currentPos, MouseEvent::NOMODE ) );
}

void
Handler::key_callBack (
		int key,
		int scancode,
		int action,
		int mods
)
{
	/// Определяем нажатую клавишу
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
			button_type = KeyEvent::KEY_SPACE;
			break;
		case GLFW_KEY_APOSTROPHE:
			button_type = KeyEvent::KEY_APOSTROPHE;
			break;
		case GLFW_KEY_COMMA:
			button_type = KeyEvent::KEY_COMMA;
			break;
		case GLFW_KEY_MINUS:
			button_type = KeyEvent::KEY_MINUS;
			break;
		case GLFW_KEY_PERIOD:
			button_type = KeyEvent::KEY_PERIOD;
			break;
		case GLFW_KEY_SLASH:
			button_type = KeyEvent::KEY_SLASH;
			break;
		case GLFW_KEY_ENTER:
			button_type = KeyEvent::KEY_ENTER;
			break;
		case GLFW_KEY_SEMICOLON:
			button_type = KeyEvent::KEY_SEMICOLON;
			break;
		case GLFW_KEY_EQUAL:
			button_type = KeyEvent::KEY_EQUAL;
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
		case GLFW_KEY_LEFT_BRACKET:
			button_type = KeyEvent::KEY_LEFT_BRACKET;
			break;
		case GLFW_KEY_RIGHT_BRACKET:
			button_type = KeyEvent::KEY_RIGHT_BRACKET;
			break;
		case GLFW_KEY_BACKSLASH:
			button_type = KeyEvent::KEY_BACKSLASH;
			break;
		case GLFW_KEY_GRAVE_ACCENT:
			button_type = KeyEvent::KEY_GRAVE_ACCENT;
			break;
		case GLFW_KEY_WORLD_1:
			button_type = KeyEvent::KEY_WORLD1;
			break;
		case GLFW_KEY_WORLD_2:
			button_type = KeyEvent::KEY_WORLD2;
			break;
		case GLFW_KEY_TAB:
			button_type = KeyEvent::KEY_TAB;
			break;
		case GLFW_KEY_BACKSPACE:
			button_type = KeyEvent::KEY_BACKSPACE;
			break;
		case GLFW_KEY_INSERT:
			button_type = KeyEvent::KEY_INSERT;
			break;
		case GLFW_KEY_DELETE:
			button_type = KeyEvent::KEY_DELETE;
			break;
		case GLFW_KEY_PAGE_UP:
			button_type = KeyEvent::KEY_PAGE_UP;
			break;
		case GLFW_KEY_PAGE_DOWN:
			button_type = KeyEvent::KEY_PAGE_DOWN;
			break;
		case GLFW_KEY_HOME:
			button_type = KeyEvent::KEY_HOME;
			break;
		case GLFW_KEY_END:
			button_type = KeyEvent::KEY_END;
			break;
		case GLFW_KEY_CAPS_LOCK:
			button_type = KeyEvent::KEY_CAPS_LOCK;
			break;
		case GLFW_KEY_NUM_LOCK:
			button_type = KeyEvent::KEY_NUM_LOCK;
			break;
		case GLFW_KEY_SCROLL_LOCK:
			button_type = KeyEvent::KEY_SCROLL_LOCK;
			break;
		case GLFW_KEY_PRINT_SCREEN:
			button_type = KeyEvent::KEY_PRINT_SCREEN;
			break;
		case GLFW_KEY_PAUSE:
			button_type = KeyEvent::KEY_PAUSE;
			break;
		case GLFW_KEY_F1:
			button_type = KeyEvent::KEY_F1;
			break;
		case GLFW_KEY_F2:
			button_type = KeyEvent::KEY_F2;
			break;
		case GLFW_KEY_F3:
			button_type = KeyEvent::KEY_F3;
			break;
		case GLFW_KEY_F4:
			button_type = KeyEvent::KEY_F4;
			break;
		case GLFW_KEY_F5:
			button_type = KeyEvent::KEY_F5;
			break;
		case GLFW_KEY_F6:
			button_type = KeyEvent::KEY_F6;
			break;
		case GLFW_KEY_F7:
			button_type = KeyEvent::KEY_F7;
			break;
		case GLFW_KEY_F8:
			button_type = KeyEvent::KEY_F8;
			break;
		case GLFW_KEY_F9:
			button_type = KeyEvent::KEY_F9;
			break;
		case GLFW_KEY_F10:
			button_type = KeyEvent::KEY_F10;
			break;
		case GLFW_KEY_F11:
			button_type = KeyEvent::KEY_F11;
			break;
		case GLFW_KEY_F12:
			button_type = KeyEvent::KEY_F12;
			break;
		case GLFW_KEY_F13:
			button_type = KeyEvent::KEY_F13;
			break;
		case GLFW_KEY_F14:
			button_type = KeyEvent::KEY_F14;
			break;
		case GLFW_KEY_F15:
			button_type = KeyEvent::KEY_F15;
			break;
		case GLFW_KEY_F16:
			button_type = KeyEvent::KEY_F16;
			break;
		case GLFW_KEY_F17:
			button_type = KeyEvent::KEY_F17;
			break;
		case GLFW_KEY_F18:
			button_type = KeyEvent::KEY_F18;
			break;
		case GLFW_KEY_F19:
			button_type = KeyEvent::KEY_F19;
			break;
		case GLFW_KEY_F20:
			button_type = KeyEvent::KEY_F20;
			break;
		case GLFW_KEY_F21:
			button_type = KeyEvent::KEY_F21;
			break;
		case GLFW_KEY_F22:
			button_type = KeyEvent::KEY_F22;
			break;
		case GLFW_KEY_F23:
			button_type = KeyEvent::KEY_F23;
			break;
		case GLFW_KEY_F24:
			button_type = KeyEvent::KEY_F24;
			break;
		case GLFW_KEY_F25:
			button_type = KeyEvent::KEY_F25;
			break;
		case GLFW_KEY_KP_0:
			button_type = KeyEvent::KEY_KP_0;
			break;
		case GLFW_KEY_KP_1:
			button_type = KeyEvent::KEY_KP_1;
			break;
		case GLFW_KEY_KP_2:
			button_type = KeyEvent::KEY_KP_2;
			break;
		case GLFW_KEY_KP_3:
			button_type = KeyEvent::KEY_KP_3;
			break;
		case GLFW_KEY_KP_4:
			button_type = KeyEvent::KEY_KP_4;
			break;
		case GLFW_KEY_KP_5:
			button_type = KeyEvent::KEY_KP_5;
			break;
		case GLFW_KEY_KP_6:
			button_type = KeyEvent::KEY_KP_6;
			break;
		case GLFW_KEY_KP_7:
			button_type = KeyEvent::KEY_KP_7;
			break;
		case GLFW_KEY_KP_8:
			button_type = KeyEvent::KEY_KP_8;
			break;
		case GLFW_KEY_KP_9:
			button_type = KeyEvent::KEY_KP_9;
			break;
		case GLFW_KEY_KP_DECIMAL:
			button_type = KeyEvent::KEY_KP_DECIMAL;
			break;
		case GLFW_KEY_KP_DIVIDE:
			button_type = KeyEvent::KEY_KP_DIVIDE;
			break;
		case GLFW_KEY_KP_MULTIPLY:
			button_type = KeyEvent::KEY_KP_MULTIPLY;
			break;
		case GLFW_KEY_KP_SUBTRACT:
			button_type = KeyEvent::KEY_KP_SUBTRACT;
			break;
		case GLFW_KEY_KP_ADD:
			button_type = KeyEvent::KEY_KP_ADD;
			break;
		case GLFW_KEY_KP_ENTER:
			button_type = KeyEvent::KEY_KP_ENTER;
			break;
		case GLFW_KEY_KP_EQUAL:
			button_type = KeyEvent::KEY_KP_EQUAL;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			button_type = KeyEvent::KEY_LEFT_SHIFT;
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			button_type = KeyEvent::KEY_RIGHT_SHIFT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			button_type = KeyEvent::KEY_LEFT_CTRL;
			break;
		case GLFW_KEY_LEFT_ALT:
			button_type = KeyEvent::KEY_LEFT_ALT;
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			button_type = KeyEvent::KEY_RIGHT_CTRL;
			break;
		case GLFW_KEY_RIGHT_ALT:
			button_type = KeyEvent::KEY_RIGHT_ALT;
			break;
		case GLFW_KEY_RIGHT_SUPER:
			button_type = KeyEvent::KEY_RIGHT_SUPER;
			break;
		case GLFW_KEY_LEFT_SUPER:
			button_type = KeyEvent::KEY_LEFT_SUPER;
			break;
		case GLFW_KEY_MENU:
			button_type = KeyEvent::KEY_MENU;
			break;
		default:
			button_type = KeyEvent::NOBUTTON;
	}
	/// Определяем мод
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
	/// Определяем тип события
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
		double xoffset,
		double yoffset
)
{
	mouseWheelEvent ( { yoffset, Event::NOMODE } );
}

void
Handler::makeCurrent ()
{
	Interceptor::initialize ( this );
	glfwSetMouseButtonCallback ( m_window, Interceptor::mouseButtonCallBack );
	glfwSetCursorPosCallback ( m_window, Interceptor::mouseMoveCallBack );
	glfwSetKeyCallback ( m_window, Interceptor::keyButtonCallBack );
	glfwSetScrollCallback ( m_window, Interceptor::scrollCallBack );
}
