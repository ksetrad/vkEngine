//
// Created by Владимир on 26.08.2020.
//

#ifndef TOOLS_CONFIGURATION_H
#define TOOLS_CONFIGURATION_H

#include "tools/toml++/toml.hpp"

class Configuration
    {

    public:
        /// Конфигурации ядра
        struct CoreVulkan
            {
                /// Название приложения
                std::string appName;

                /// Название движка
                std::string engineName;

                /// Массив Уровней валидации
                std::vector < std::string > validationLayers;

                /// Массив используемых расшираений
                std::vector < std::string > deviceExtension;

                /// Сформировать массив си-строк имен уровней валидации
                /// \return Массив
                [[nodiscard]] std::vector < const char * >
                getValidationLayersArr () const
                {
                        std::vector < const char * > result;
                        for ( const auto & str: validationLayers )
                        {
                                result.push_back ( str.c_str () );
                        }
                        return result;
                }

                /// Сформировать массив си-строк имен расширений
                /// \return Массив
                [[nodiscard]] std::vector < const char * >
                getDeviceExtensions () const
                {
                        std::vector < const char * > result;
                        for ( const auto & str: deviceExtension )
                        {
                                result.push_back ( str.c_str () );
                        }
                        return result;
                }
            };

        /// Параметры дисплея вывода
        struct Display
            {
                struct
                /// Разрешение
                    {
                        /// Ширина
                        int width;
                        /// Высота
                        int height;
                    } resolution;
            };


        virtual ~Configuration ();

        /// Параметры ядра
        /// \return параметры ядра
        static const CoreVulkan &
        vulkan ();

        /// Параметры дисплея
        /// \return параметры дисплея
        static const Display &
        display ();

    private:
        /// Конструктор()
        Configuration ();

        /// Считать конфигурацию из файла
        void
        read ();

        /// Записать конфигурацию в файл
        void
        write ();

        /// Синглтон конфигурации
        /// \return экземпляр
        static Configuration *
        instance ();

        /// Конфигуарция ядра
        CoreVulkan m_vulkan;

        /// Конфигурация дисплея
        Display m_display;
    };

#endif //TOOLS_CONFIGURATION_H
