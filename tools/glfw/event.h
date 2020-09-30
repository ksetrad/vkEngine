//
// Created by Владимир on 14.09.2020.
//

#ifndef TOOLS_GLFW_EVENT_H
#define TOOLS_GLFW_EVENT_H

#include <glm/vec2.hpp>

namespace glfw
{
	struct Event
	{
		enum Mods
		{
			NOMODE,
			SHIFT,
			CTRL,
			ALT
		};

		explicit Event ( const Mods & m_mod );

		Mods m_mod;
	};

	class MouseEvent : public Event
	{

		public:
			enum MouseButtons
			{
				NOBUTTON,
				MOUSE_LEFT_BUTTON,
				MOUSE_RIGHT_BUTTON,
				MOUSE_WHEEL
			};

			MouseEvent (
					MouseButtons mButton,
					const glm::vec2 & mPos,
					const Mods & mMod
			);

			[[nodiscard]] const MouseButtons &
			button () const
			{
				return m_button;
			}

			[[nodiscard]] const glm::vec2 &
			pos () const
			{
				return m_pos;
			}

			[[nodiscard]] const Mods &
			mod () const
			{
				return m_mod;
			}

		private:
			MouseButtons m_button;

			glm::vec2 m_pos;
	};

	class KeyEvent : public Event
	{
		public:
			enum KeyButtons
			{
				NOBUTTON,
				KEY_0,
				KEY_1,
				KEY_2,
				KEY_3,
				KEY_4,
				KEY_5,
				KEY_6,
				KEY_7,
				KEY_8,
				KEY_9,
				KEY_A,
				KEY_B,
				KEY_C,
				KEY_D,
				KEY_E,
				KEY_F,
				KEY_G,
				KEY_I,
				KEY_J,
				KEY_H,
				KEY_K,
				KEY_L,
				KEY_M,
				KEY_N,
				KEY_O,
				KEY_P,
				KEY_Q,
				KEY_R,
				KEY_S,
				KEY_T,
				KEY_U,
				KEY_V,
				KEY_W,
				KEY_X,
				KEY_Y,
				KEY_Z,
				KEY_ESC,
				KEY_ENTER,
				KEY_SPACEBAR,
				KEY_UP,
				KEY_DOWN,
				KEY_LEFT,
				KEY_RIGHT,
				KEY_BACKSPACE,
				KEY_TILDA,
				KEY_LEFT_SLASH,
				KEY_RIGHT_SLASH,
				KEY_TAB,
				KEY_COMMA
			};

			KeyEvent (
					KeyButtons mButton,
					const Mods & mMod
			);

			[[nodiscard]] const KeyButtons &
			button () const
			{
				return m_button;
			}

			[[nodiscard]] const Mods &
			mod () const
			{
				return m_mod;
			}

		private:
			KeyButtons m_button;
	};

	class MouseWheelEvent : public Event
	{
		public:
			MouseWheelEvent (
					double delta,
					const Mods & mMod
			);


			[[nodiscard]] const double &
			delta () const;

		private:
			double m_delta;
	};
}// namespace glfw
#endif//TOOLS_GLFW_EVENT_H
