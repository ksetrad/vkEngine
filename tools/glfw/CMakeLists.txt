set(glfw_tools_src
        ${project_dir}/tools/glfw/event.cpp
        ${project_dir}/tools/glfw/interceptor.cpp
        ${project_dir}/tools/glfw/handler.cpp)

add_library(glfw_tools
        OBJECT
        ${glfw_tools_src})