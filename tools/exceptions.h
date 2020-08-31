//
// Created by Владимир on 04.08.2020.
//
/// \file
/// \brief Шаблоны готовых исключений (в виде макросов)

#ifndef TOOLS_EXCEPTIONS_H
#define TOOLS_EXCEPTIONS_H

#include "tools/exception.h"

#define verify( statement , msg ) ((!statement)? throw tools::Exception(__LINE__, __FILE__,std::string("VULKAN_EXCEPTION: ") + msg):0)

/// Шаблоны готовых исключений
#define vulkan_exception( msg ) (tools::Exception(__LINE__, __FILE__,std::string("VULKAN_EXCEPTION: ") + msg))

#define file_not_found_exception( name ) (tools::Exception(__LINE__, __FILE__,std::string("File not found: ") + name))

#define glfw_exception( msg ) (tools::Exception(__LINE__, __FILE__,std::string("GLFW_EXCEPTION: ") + msg))

#define window_exception( msg ) (tools::Exception(__LINE__, __FILE__,std::string("WINDOW_EXCEPTION:") + msg))

#endif //TOOLS_EXCEPTIONS_H
