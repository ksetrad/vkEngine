add_library(configuration
        OBJECT
        ${project_dir}/tools/configuration.cpp)

add_library(logger
        OBJECT
        ${project_dir}/tools/logger.cpp)

include(${project_dir}/tools/vk/CMakeLists.txt)
include(${project_dir}/tools/glfw/CMakeLists.txt)