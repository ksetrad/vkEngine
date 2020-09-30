//
// Created by Владимир on 14.09.2020.
//

#ifndef TOOLS_GLFW_INTERCEPTOR_H
#define TOOLS_GLFW_INTERCEPTOR_H

#include <GLFW/glfw3.h>


namespace glfw
{
	class Handler;

	/// Синглтон перехвата событий glwf
	class Interceptor
	{
		public:
			/// \brief Перехват события нажатия мыши
			/// \param window Активное окно
			/// \param button кнопка
			/// \param action событие
			/// \param mods мод
			static void
			mouseButtonCallBack (
					GLFWwindow * window,
					int button,
					int action,
					int mods
			);

			/// \brief Перехват события нажатия клавиши клавиатуры
			/// \param window Активное окно
			/// \param key клавиша
			/// \param scancode TODO платформозависимая хрень, которая означает, что на разных платформах одна и таже кнопка может иметь разный код
			/// \param action Событие
			/// \param mods мод
			static void
			keyButtonCallBack (
					GLFWwindow * window,
					int key,
					int scancode,
					int action,
					int mods
			);

			/// \brief Перехватчик смещения мыши
			/// \param window Активное окно
			/// \param xpos Х координата
			/// \param ypos Y координата
			static void
			mouseMoveCallBack (
					GLFWwindow * window,
					double xpos,
					double ypos
			);

			/// \brief Перехватчик события скроллинга
			/// \param window Активное окно
			/// \param xoffset смещение по Х
			/// \param yoffset смещение по Y (только оно и используется)
			static void
			scrollCallBack (
					GLFWwindow * window,
					double xoffset,
					double yoffset
			);

			/// \brief Получить синглтон
			/// \return синглтон
			static Interceptor *
			instance ();

			/// \brief Инициализация обработчиком
			/// \param handler обработчик
			static void
			initialize ( Handler * handler );

		private:
			/// Текущий обработчик
			Handler * handler;
	};
}// namespace glfw
#endif//TOOLS_GLFW_INTERCEPTOR_H
