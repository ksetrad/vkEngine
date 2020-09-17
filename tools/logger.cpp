//
// Created by idalov on 15.11.2019.
//

#include <csignal>
#include <cstring>
#include <dirent.h>
#include <list>
#include <sstream>
#include <sys/stat.h>
#include <utility>

#include "tools/exception.h"
#include "tools/logger.h"

std::unique_ptr < Logger > Logger::logger ( nullptr );

Logger::Logger ( std::string path ) :
		m_default_buffer ( nullptr ),
		m_path ( std::move ( path ) )
{
	/// Инициализируются текстовые расшифровки уровней информативности
	m_levels.emplace ( info, "INFO" );
	m_levels.emplace ( warning, "WARNING" );
	m_levels.emplace ( error, "ERROR" );
	/// Проверяется содержимое директории
	checkDirContent ( "log" );
	/// Формируется файл основного журнала
	auto current_time = std::chrono::system_clock::to_time_t ( std::chrono::system_clock::now () );
	auto time = std::localtime ( &current_time );
	std::stringstream fileName;
	fileName<<m_path + "/log"<<time->tm_year + 1900<<'_'<<time->tm_mon + 1<<'_'<<time->tm_mday
	        <<'_'
	        <<time->tm_hour<<'_'<<time->tm_min<<'_'<<time->tm_sec<<".txt";
	m_log_file.open ( fileName.str () );
	m_default_buffer = m_log_file.rdbuf ();
}

Logger::~Logger ()
{
	/// Закрываются файлы журнала
	close ();
}

void
Logger::close ()
{
	/// Закрывается основной журнал
	instance ()->m_log_file.close ();
	/// Закрываются журналы компонентов (если такие имеются)
	for (
		auto &component : instance ()->m_components )
	{
		if ( component.second.first.personalLog )
		{
			component.second.second.close ();
		}
	}
}

std::string
Logger::buildTitle (
		const Logger::Level &level
)
{
	/// Формируется заголовк сообщения [год-месяц-день хх:хх:хх] (уровень информативности сообщения) [идентификатор потока]
	std::string title;
	auto current_time = std::chrono::system_clock::to_time_t ( std::chrono::system_clock::now () );
	auto time = std::localtime ( &current_time );
	std::stringstream date;
	date<<'['<<time->tm_year + 1900<<'-'<<time->tm_mon + 1<<'-'<<time->tm_mday<<'\040'
	    <<time->tm_hour
	    <<':'
	    <<time->tm_min<<':'<<time->tm_sec<<']'<<'\040';
	title += ( date.str () + '(' + m_levels.at ( level ) + ')' + '\040' +
	           getThreadIndex ( std::this_thread::get_id () ) ) +
	         '\040';
	return title;
}

std::string
Logger::getThreadIndex ( const std::thread::id &id )
{
	/// Каждому новому потоку, поялвяющемуся в логере присваивается следующий порядковый номер
	static std::size_t nextIndex = 0;
	static std::map < std::thread::id, std::string > ids;
	if ( ids.find ( id ) == ids.end () )
	{
		std::stringstream strs;
		strs<<"[Thread#"<<nextIndex++<<"]";
		Logger::instance ()->m_log_file<<" Add thread "<<std::dec<<nextIndex - 1;
		Logger::instance ()->m_log_file<<" as "<<std::hex<<id<<std::dec<<'\n';
		Logger::instance ()->m_log_file.flush ();
		ids[ id ] = strs.str ();
	}
	/// Возвращаенися строковый идентификатор потока
	return ids[ id ];
}

void
Logger::addComponent (
		std::string name,
		const std::string &alias,
		const Level &verbosity,
		const bool &personalLog
)
{
	/// Проверяется наличие модуля с данным псевдонимом в журнале
	if ( instance ()->m_components.find ( Alias ( alias ) ) != instance ()->m_components.end () )
	{
		throw tools::Exception ( __LINE__, __FILE__, "Component already exist" );
	}
	if ( personalLog )
	{
		/// Проверяется содержимое директории журналов
		instance ()->checkDirContent ( alias );
		/// Формируется имя файла
		auto current_time = std::chrono::system_clock::to_time_t ( std::chrono::system_clock::now () );
		auto time = std::localtime ( &current_time );
		std::stringstream fileName;
		fileName<<instance ()->m_path + "/"<<alias<<time->tm_year + 1900<<'_'<<time->tm_mon + 1<<'_'
		        <<time->tm_mday
		        <<'_'
		        <<time->tm_hour<<'_'<<time->tm_min<<'_'<<time->tm_sec<<".txt";
		/// Модуль сохраняется в журнале, а также открывается файловый поток модуля
		instance ()->m_components.emplace ( Alias ( alias ),
		                                    std::make_pair (
				                                    Component ( std::move ( name ), alias, verbosity,
				                                                personalLog ),
				                                    std::ofstream ( fileName.str () ) ) );
	}
	else
	{
		/// Компоненты без персонализации лог файла используют стандартный журнал
		instance ()->m_components.emplace ( Alias ( alias ),
		                                    std::make_pair (
				                                    Component ( std::move ( name ), alias, verbosity,
				                                                personalLog ),
				                                    std::ofstream () ) );
	}
}

Logger::Component
Logger::findComponent ( const Alias &alias )
{
	/// Проверяется наличия модуля с заданным псевдонимом в журнале
	if ( instance ()->m_components.find ( alias ) == instance ()->m_components.end () )
	{
		throw tools::Exception ( __LINE__, __FILE__, "Component don't exist" );
	}
	return instance ()->m_components.at ( alias ).first;
}

void
Logger::checkDirContent ( const std::string &keyWord )
{
	/// Осуществляется поиск файлов в дирректории хранения журналов по заданному ключевому слову
	DIR *pDir;
	dirent *entry;
	pDir = opendir ( m_path.c_str () );
	std::map < Date, std::string > candidates;
	while ( ( entry = readdir ( pDir ) ) )
	{
		if ( strcmp ( entry->d_name, "." ) != 0 && strcmp ( entry->d_name, ".." ) != 0 )
		{
			std::string fName ( entry->d_name );
			if ( fName.find ( keyWord ) != std::string::npos )
			{
				candidates.emplace ( Date ( fName ), fName );
			}
		}
	}
	/// Если в директории больше 5 лог файлов то самые старые будут удаляться до тех пор пока не останется 4 файла с заданным ключем
	while ( candidates.size () > 4 )
	{
		remove ( ( m_path + "/" + candidates.begin ()->second ).c_str () );
		candidates.erase ( candidates.begin () );
	}
}

void
Logger::setVerbosity ( const Logger::Level &level )
{
	instance ()->minLevel = level;
}

void
Logger::setGlobalDirPath ( const std::string &path )
{
	/// ВНИМАНИЕ! Рекомендуется вызывать данный метод первым в программе
	/// При установке новой директории хранения осуществляется формирование нового журнала.
	logger = std::unique_ptr < Logger > ( new Logger ( path ) );
}

void
Logger::resetBufferToDefault ()
{
	/// Захват мьютекса
	std::lock_guard < std::mutex > guard ( instance ()->mutex );
	static_cast< std::ostream * > ( &instance ()->m_log_file )->rdbuf ( instance ()->m_default_buffer );
}

bool
Logger::Date::operator< ( const Logger::Date &rhs ) const
{
	if ( year < rhs.year )
	{
		return true;
	}
	else
	{
		if ( year > rhs.year )
		{
			return false;
		}
		else
		{
			if ( mon < rhs.mon )
			{
				return true;
			}
			else
			{
				if ( mon > rhs.mon )
				{
					return false;
				}
				else
				{
					if ( day < rhs.day )
					{
						return true;
					}
					else
					{
						if ( day > rhs.day )
						{
							return false;
						}
						else
						{
							if ( hour < rhs.hour )
							{
								return true;
							}
							else
							{
								if ( hour > rhs.hour )
								{
									return false;
								}
								else
								{
									if ( min < rhs.min )
									{
										return true;
									}
									else
									{
										if ( min > rhs.min )
										{
											return false;
										}
										else
										{
											return sec < rhs.sec;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

bool
Logger::Date::operator> ( const Logger::Date &rhs ) const
{
	return rhs < *this;
}

Logger::Date::Date (
		const std::string &str
)
{
	uint32_t first = str.find ( '_' );
	year = std::stoi ( str.substr ( str.find ( '2' ), first ) );
	uint32_t last = str.find ( '_', first + 1 );
	mon = std::stoi ( str.substr ( first + 1, last ) );
	first = last;
	last = str.find ( '_', first + 1 );
	day = std::stoi ( str.substr ( first + 1, last ) );
	first = last;
	last = str.find ( '_', first + 1 );
	hour = std::stoi ( str.substr ( first + 1, last ) );
	first = last;
	last = str.find ( '_', first + 1 );
	min = std::stoi ( str.substr ( first + 1, last ) );
	first = last;
	last = str.find ( '.', first + 1 );
	sec = std::stoi ( str.substr ( first + 1, last ) );
}
