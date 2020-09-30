//
// Created by Владимир on 14.09.2020.
//

#ifndef TOOLS_GLFW_EVENT_H
#define TOOLS_GLFW_EVENT_H

#include <glm/vec2.hpp>

namespace glfw
{
	/// \brief Событие
	struct Event
	{
		/// Мод при котором происходит событие
		enum Mods
		{
			NOMODE,
			SHIFT,
			CTRL,
			ALT
		};

		/// \brief Конструктор
		/// \param m_mod Мод (shift, alt, ctrl)
		explicit Event ( const Mods & m_mod );

		Mods m_mod;
	};

	/// \brief Событие мыши
	class MouseEvent : public Event
	{

		public:
			/// \brief Доступные кнопки мыши
			enum MouseButtons
			{
				NOBUTTON,
				MOUSE_LEFT_BUTTON,
				MOUSE_RIGHT_BUTTON,
				MOUSE_WHEEL,
				MOUSE_BUTTON4,
				MOUSE_BUTTON5,
				MOUSE_BUTTON6,
				MOUSE_BUTTON7,
				MOUSE_BUTTON8
			};

			/// \brief Конструктор
			/// \param mButton нажатая кнопка
			/// \param mPos позиция мыши в экранных координатах
			/// \param mMod мод
			MouseEvent (
					MouseButtons mButton,
					const glm::vec2 & mPos,
					const Mods & mMod
			);

			/// \brief Получить нажатую кнопку
			/// \return Кнопка
			[[nodiscard]] const MouseButtons &
			button () const
			{
				return m_button;
			}

			/// \brief Получить позицию мыши в экранных координатах
			/// \return координата
			[[nodiscard]] const glm::vec2 &
			pos () const
			{
				return m_pos;
			}

			/// \brief Получить текущий мод
			/// \return мод
			[[nodiscard]] const Mods &
			mod () const
			{
				return m_mod;
			}

		private:
			/// Нажатая клавиша
			MouseButtons m_button;

			/// Экранные координаты
			glm::vec2 m_pos;
	};

	/// \brief Событие клавиатуры
	class KeyEvent : public Event
	{
		public:
			/// \brief Доступные клавиши клавиатуры
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
				KEY_SPACE,
				KEY_APOSTROPHE,
				KEY_COMMA,
				KEY_MINUS,
				KEY_PERIOD,
				KEY_SLASH,
				KEY_SEMICOLON,
				KEY_EQUAL,
				KEY_UP,
				KEY_DOWN,
				KEY_LEFT,
				KEY_RIGHT,
				KEY_LEFT_BRACKET,
				KEY_RIGHT_BRACKET,
				KEY_BACKSLASH,
				KEY_GRAVE_ACCENT,
				KEY_WORLD1,
				KEY_WORLD2,
				KEY_TAB,
				KEY_BACKSPACE,
				KEY_INSERT,
				KEY_DELETE,
				KEY_PAGE_UP,
				KEY_PAGE_DOWN,
				KEY_HOME,
				KEY_END,
				KEY_CAPS_LOCK,
				KEY_NUM_LOCK,
				KEY_SCROLL_LOCK,
				KEY_PRINT_SCREEN,
				KEY_PAUSE,
				KEY_F1,
				KEY_F2,
				KEY_F3,
				KEY_F4,
				KEY_F5,
				KEY_F6,
				KEY_F7,
				KEY_F8,
				KEY_F9,
				KEY_F10,
				KEY_F11,
				KEY_F12,
				KEY_F13,
				KEY_F14,
				KEY_F15,
				KEY_F16,
				KEY_F17,
				KEY_F18,
				KEY_F19,
				KEY_F20,
				KEY_F21,
				KEY_F22,
				KEY_F23,
				KEY_F24,
				KEY_F25,
				KEY_KP_1,
				KEY_KP_2,
				KEY_KP_3,
				KEY_KP_4,
				KEY_KP_5,
				KEY_KP_6,
				KEY_KP_7,
				KEY_KP_8,
				KEY_KP_9,
				KEY_KP_0,
				KEY_KP_DECIMAL,
				KEY_KP_DIVIDE,
				KEY_KP_MULTIPLY,
				KEY_KP_SUBTRACT,
				KEY_KP_ADD,
				KEY_KP_ENTER,
				KEY_KP_EQUAL,
				KEY_LEFT_SHIFT,
				KEY_RIGHT_SHIFT,
				KEY_LEFT_CTRL,
				KEY_RIGHT_CTRL,
				KEY_LEFT_ALT,
				KEY_RIGHT_ALT,
				KEY_LEFT_SUPER,
				KEY_RIGHT_SUPER,
				KEY_MENU
			};

			/// \brief Конструктор
			/// \param mButton нажатая клавиша
			/// \param mMod мод
			KeyEvent (
					KeyButtons mButton,
					const Mods & mMod
			);

			/// \brief Получить нажатую клавишу
			/// \return клавиша
			[[nodiscard]] const KeyButtons &
			button () const
			{
				return m_button;
			}

			/// \brief Получить мод
			/// \return мод
			[[nodiscard]] const Mods &
			mod () const
			{
				return m_mod;
			}

		private:
			/// Нажатая клавиша
			KeyButtons m_button;
	};

	/// \brief Событие скролинга
	class MouseWheelEvent : public Event
	{
		public:
			/// \brief Конструктор
			/// \param delta скроллинг вверх (+) вниз (-)
			/// \param mMod
			MouseWheelEvent (
					double delta,
					const Mods & mMod
			);

			/// \brief Позиция скролинга
			/// \return
			[[nodiscard]] const double &
			delta () const;

		private:
			/// Позиция
			double m_delta;
	};
}// namespace glfw
#endif//TOOLS_GLFW_EVENT_H
