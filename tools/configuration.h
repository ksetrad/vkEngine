//
// Created by Владимир on 26.08.2020.
//

#ifndef TOOLS_CONFIGURATION_H
#define TOOLS_CONFIGURATION_H

#include "tools/toml++/toml.hpp"

class Configuration
    {

    public:
        struct CoreVulkan
            {
                std::string appName;

                std::string engineName;

                std::vector < std::string > validationLayers;

                std::vector < const char * >
                getValidationLayersArr ()
                {
                        std::vector < const char * > result;
                        for ( const auto & str: validationLayers )
                        {
                                result.push_back ( str.c_str () );
                        }
                        return result;
                }
            };

        struct Display
            {
                struct
                    {
                        int width;
                        int height;
                    } resolution;
            };


        virtual ~Configuration ();

        static const CoreVulkan &
        vulkan ();

        static const Display &
        display ();

    private:

        Configuration ();

        void
        read ();

        void
        write ();

        static Configuration *
        instance ();

        CoreVulkan m_vulkan;

        Display m_display;

    };

#endif //TOOLS_CONFIGURATION_H
