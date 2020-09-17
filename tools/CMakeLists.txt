add_library(configuration
        OBJECT
        ${project_dir}/tools/configuration.cpp)

add_library(logger
        OBJECT
        ${project_dir}/tools/logger.cpp)

include(${project_dir}/tools/vk/CMakeLists.txt)

if(UNIX)
    add_subdirectory(${project_dir}/tools/glfw-3.3.2/)
endif()