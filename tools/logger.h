//
// Created by idalov on 15.11.2019.
//

#ifndef EXTLIBS_LOGGER_H
#define EXTLIBS_LOGGER_H

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

/// \brief Класс модульного журнала сообщений.
/// Модуль представляет собой часть журнала с особыми настройками вывода информации.
/// Добавление модуля осуществляется с помощью метода addComponent
/// Запись сообщений в журнал осуществляется с помощью метода message
class Logger
{
	public:
	/// \brief Уровни информативности сообщений
	enum Level
	{
		/// Информация
		info,
		/// Предупреждение
		warning,
		/// Ошибка. Сообщения с ошибками всегда выводятся в консоль
		error
	};

	/// Класс псевдонима модуля
	class Alias
	{
		public:
		/// \brief Конструктор
		/// \param name Псевдоним модуля в журнале
		explicit Alias ( std::string name ) :
		    alias ( std::move ( name ) )
		{
		}

		bool
		operator< ( const Alias &rhs ) const
		{
			return alias < rhs.alias;
		}

		private:
		/// Значение псевдонима
		std::string alias;
	};

	/// \brief Процедура записи сообщения в журнал
	/// \tparam Args Типы аргументов
	/// \param level Информативность сообщения
	/// \param args Выводимые в сообщении значения
	template < typename... Args >
	static void
	message (
	        const Level &level,
	        Args... args )
	{
		/// Захват мьютекса
		std::lock_guard< std::mutex > guard ( instance ()->mutex );
		/// Осуществляется проверка возможности вывода сообщения в журнал
		if ( instance ()->minLevel <= level )
		{
			/// Формируется заголовок сообщения
			auto title = instance ()->buildTitle ( level ) + R"(: )";
			/// Осуществляется запись сообщения в журнал
			instance ()->m_log_file << title;
			instance ()->message ( &instance ()->m_log_file, args... );
			/// Сообщения с ошибками дублируются в консоль
			if ( level == error )
			{
				std::cout << title;
				instance ()->message ( &std::cout, args... );
			}
		}
	}

	static void
	setCustomBuffer ( std::streambuf *custom_buf )
	{
		/// Захват мьютекса
		std::lock_guard< std::mutex > guard ( instance ()->mutex );
		static_cast< std::ostream * > ( &instance ()->m_log_file )->rdbuf ( custom_buf );
	}

	/// \brief Процедура записи сообщения в журнал, используя настройки модуля
	/// \tparam Args Типы аргументов
	/// \param level Информативность сообщения
	/// \param using_component Используемый модуль журнала
	/// \param args Выводимые в сообщении значения
	template < typename... Args >
	static void
	message (
	        const Level &level,
	        const Alias &using_component,
	        Args... args )
	{
		/// Захват мьютекса
		std::lock_guard< std::mutex > guard ( instance ()->mutex );
		/// Проверяется существование заправшиваемого модуля
		auto component = findComponent ( using_component );
		/// Осуществляется проверка возможности вывода сообщения в журнал
		if ( component.verbosity <= level )
		{
			/// Формируется заголовок
			auto title = instance ()->buildTitle ( level ) + component.name + R"( : )";
			/// Осуществляется выбор файла журнала для модуля
			/// Сообщения записывается в журнал
			if ( component.personalLog )
			{
				auto stream = &instance ()->m_components.at ( using_component ).second;
				*stream << title;
				instance ()->message ( stream, args... );
			}
			else
			{
				instance ()->m_log_file << title;
				instance ()->message ( &instance ()->m_log_file, args... );
			}
			/// Сообщения с ошибками дублируются в консоль
			if ( level == error )
			{
				std::cout << title;
				instance ()->message ( &std::cout, args... );
			}
		}
	}

	/// \brief Добавление модуля в журнал
	/// \param name Имя модуля
	/// \param alias Псевдоним модуля
	/// \param verbosity Нижняя граница информативности выводимых сообщений
	/// \param personalLog Наличие персонального лог-файла для модуля
	static void
	addComponent (
	        std::string name,
	        const std::string &alias,
	        const Level &verbosity = Level::info,
	        const bool &personalLog = false );

	/// \brief Установка минимального уровня информативности сообщений выводимых в основном журнале
	/// \param level Минимальный уровень информативности
	static void
	setVerbosity ( const Level &level );

	static void
	resetBufferToDefault ();

	/// \brief Установка директории хранения логов журнала
	/// \param path Путь к директории
	static void
	setGlobalDirPath ( const std::string &path );

	/// \brief Деструктор
	~Logger ();

	private:
	/// \brief Модуль с персонализацией настроек вывода сообщений
	struct Component {
		/// Уровень подробности
		Level verbosity { info };

		/// Псевдоним
		std::string alias;

		/// Отображаемое имя
		std::string name;

		/// Использование персонального лог_файла
		bool personalLog;

		/// \brief Конструктор
		/// \param name Имя компонента
		/// \param alias Псевдоним
		/// \param verbosity Уровень подробности сообщений
		/// \param personalLog Признак наличия персонального лог файла
		Component (
		        std::string name,
		        std::string alias,
		        const Level &verbosity = Level::info,
		        const bool &personalLog = false ) :
		    verbosity ( verbosity ),
		    alias ( std::move ( alias ) ),
		    name ( std::move ( name ) ),
		    personalLog ( personalLog )
		{
		}
	};

	/// \brief Поиск модуля в журнале по псевдониму
	/// \param alias Псевдоним
	/// \return Компонент
	static Component
	findComponent ( const Alias &alias );

	/// \brief Функция получения указателя на синглтон
	/// \return Указатель на синглтон
	inline static Logger *
	instance ()
	{
		if ( logger == nullptr )
		{
			/// Объект журнала будет инициализирован, если он не был инициализирован ранее
			logger = std::unique_ptr< Logger > ( new Logger () );
		}
		return logger.get ();
	}

	/// \brief Разбор сообщения
	/// \tparam CurrentType Тип выводимого аргумента
	/// \tparam Others Типы оставшихся аргументов
	/// \param stream Поток вывода
	/// \param next Выводимый аргумент
	/// \param args Остальные аргументы
	template < typename CurrentType, typename... Others >
	void
	message (
	        std::ostream *stream,
	        CurrentType next,
	        Others... args )
	{
		/// Вывод аргумента
		*stream << next << '\040';
		/// Продолжается разбор аргументов в сообщении
		message ( stream, args... );
	}

	/// \brief Разбор сообщения
	/// \tparam CurrentType Тип выводимого аргумента
	/// \param stream Поток вывода
	/// \param next Выводимый аргумент
	template < typename CurrentType >
	void
	message (
	        std::ostream *stream,
	        CurrentType next )
	{
		*stream << next << '\n';
		/// Сообщение заносится в файл журнала
		stream->flush ();
	}

	/// \brief Процедура закрытия лог-файлов
	static void
	close ();

	/// \brief Проверка содержимого директории по псевданиму лог файла, на наличие других лог файлов с данным псевдонимом
	/// \param keyWord Псевдоним
	void
	checkDirContent ( const std::string &keyWord );

	/// \brief Конструктор
	/// \param path Путь к директории хранения логов
	explicit Logger ( std::string path = "./logs" );

	/// \brief Функция формирования заголовка сообщения
	/// \param level Уровень подробности сообщения
	/// \return Заголовк
	std::string
	buildTitle (
	        const Level &level );

	/// \brief Функция определения номера потока, формирующего сообщение
	/// \param id Идентификатор потока
	/// \return Номер потока в журнале
	static std::string
	getThreadIndex ( const std::thread::id &id );


	/// Указатель на синглтон
	static std::unique_ptr< Logger > logger;

	/// Массив текстовых расшифровок уровней подробности
	std::map< Level, std::string > m_levels;

	/// Массив компонентов
	std::map< Alias, std::pair< Component, std::ofstream > > m_components;

	/// Файл журнала
	std::ofstream m_log_file;

	std::streambuf *m_default_buffer;

	/// Мьютекс
	mutable std::mutex mutex;

	/// Путь к директории хранения журналов
	std::string m_path;

	/// Минимальный уровень информативности сообщений в журнале
	Level minLevel { info };

	/// Структура даты
	class Date
	{
		public:
		/// \brief Конструктор формирования даты по имени файла
		/// \param str имя файла
		explicit Date ( const std::string &str );

		bool
		operator< ( const Date &rhs ) const;

		bool
		operator> ( const Date &rhs ) const;

		private:
		int hour;

		int min;

		int sec;

		int day;

		int mon;

		int year;
	};
};

#endif//EXTLIBS_LOGGER_H
