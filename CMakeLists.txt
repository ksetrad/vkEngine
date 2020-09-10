cmake_minimum_required(VERSION 3.17)
project(caravaner2)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(GLM REQUIRED)

set(project_dir ${CMAKE_SOURCE_DIR})

add_executable(caravaner2 main.cpp
        ${project_dir}/engine/core.cpp
        ${project_dir}/engine/mainRenderPass.cpp
        $<TARGET_OBJECTS:configuration>
        $<TARGET_OBJECTS:logger>
        $<TARGET_OBJECTS:vulkan_tools>
        )

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)

include_directories(${project_dir})

include(${project_dir}/tools/CMakeLists.txt)
include(${project_dir}/shaders/CMakeLists.txt)

target_include_directories(caravaner2 PUBLIC ${GLM_INCLUDE_DIR} ${Vulkan_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

target_link_libraries(caravaner2 glfw glm ${Vulkan_LIBRARY})

add_compile_definitions(VULKAN_DEBUG)