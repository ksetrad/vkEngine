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

		explicit Event ( const Mods &m_mod );

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
					const glm::vec2 &mPos,
					const Mods &mMod
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

	class KeyEvent
	{
	};
}// namespace glfw
#endif//TOOLS_GLFW_EVENT_H
