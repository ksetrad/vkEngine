//
// Created by Владимир on 04.08.2020.
//
/// \file
/// \brief Класс исключений

#ifndef TOOLS_EXCEPTION_H
#define TOOLS_EXCEPTION_H

#include <exception>
#include <sstream>
#include <string>

namespace tools
{
	/**
     * Класс исключений
     */
	class Exception :
			public std::exception
	{
		public:
			/// Конструктор
			/// \param line Линия на которой вызвано исключение
			/// \param file_path Путь к файлу в котором произошло исключение
			/// \param error_msg Сообщение с информацией для вывода в консоль
			Exception (
					const uint64_t &line,
					const std::string &file_path,
					const std::string &error_msg
			)
			{
				std::ostringstream strs;
				strs<<line;
				msg = "FILE: " + file_path + " LINE: " + strs.str () + '\n' + error_msg + '\n';
			}

			/// Функция получения сообщения по исключению
			/// \return
			[[nodiscard]] const char *
			what () const noexcept override
			{
				return msg.c_str ();
			}

		private:
			/// Сообщение
			std::string msg;
	};
}// namespace tools
#endif//TOOLS_EXCEPTION_H
