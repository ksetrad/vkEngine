//
// Created by Владимир on 14.09.2020.
//

#ifndef TOOLS_GLFW_HANDLER_H
#define TOOLS_GLFW_HANDLER_H

#include <string>
#include "event.h"

namespace glfw
{

	/// \brief Обработчик GLFW
	class Handler
	{
		public:
			/// \brief Конструктор
			/// \param width ширина окна
			/// \param height высота окна
			/// \param title Заголовок окна
			Handler (
					int width,
					int height,
					const std::string & title
			);


			/// \brief Событие нажатия клавиши мыши
			/// \param button Кнопка
			/// \param action Событие
			/// \param mods Мод
			void
			mouse_callBack (
					int button,
					int action,
					int mods
			);

			/// \brief Событие нажатия клавиши клавиатуры
			/// \param key Клавиша
			/// \param scancode Особый, платфорозависимый код клавиши
			/// \param action Событие
			/// \param mods Мод
			void
			key_callBack (
					int key,
					int scancode,
					int action,
					int mods
			);

			/// \brief Событие скролинга
			/// \param xoffset Сдвиг по X
			/// \param yoffset Сдвиг по Y
			void
			scroll_callBack (
					double xoffset,
					double yoffset
			);

			/// \brief Событие смещения мыши
			/// \param xpos Смещение по Х
			/// \param ypos Смещение по Y
			void
			mouseMove (
					double xpos,
					double ypos
			);

			/// \brief Сделать данный обработчик активным для захвата событий вводных устройств
			void
			makeCurrent();

		protected:
			/// \brief Событие смещения мыши
			/// \param event Событие мыши
			virtual void
			mouseMoveEvent ( const MouseEvent & event )
			{
			}

			/// \brief СОбытие нажатия клавиши мыши
			/// \param event Событие
			virtual void
			mousePressEvent ( const MouseEvent & event )
			{
			}

			/// \brief Событие отжатия клавиши мыши
			/// \param event Событие
			virtual void
			mouseReleaseEvent ( const MouseEvent & event )
			{
			}

			/// \brief Событие скролинга мыши
			/// \param event Событие
			virtual void
			mouseWheelEvent ( const MouseWheelEvent & event )
			{
			}

			/// \brief Событие нажатия клавиши
			/// \param event Событие
			virtual void
			keyPressEvent ( const KeyEvent & event )
			{
			}

			/// \brief Событие отжатия клавиши
			/// \param event Событие
			virtual void
			keyReleaseEvent ( const KeyEvent & event )
			{
			}

			/// \brief Событие "зажимания" клавиши клавиатуры
			/// \param event Событие
			virtual void
			keyRepeatEvent ( const KeyEvent & event )
			{
			}

			/// Активное окно
			GLFWwindow * m_window;

		private:
			/// Текущая позиция
			glm::vec2 currentPos;
	};
}// namespace glfw
#endif//TOOLS_GLFW_HANDLER_H
