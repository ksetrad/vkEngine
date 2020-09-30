cmake_minimum_required(VERSION 3.13)
project(caravaner2)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)

if (WIN32)
    find_package(GLFW3 REQUIRED)
endif()

set(project_dir ${CMAKE_SOURCE_DIR})

add_executable(caravaner2 main.cpp
        ${project_dir}/engine/core.cpp
        ${project_dir}/engine/mainRenderPass.cpp
        ${project_dir}/engine/commandPool.cpp
        ${project_dir}/engine/data/model.cpp
        ${project_dir}/engine/modelFactory.cpp
        ${project_dir}/engine/environment.cpp
        ${project_dir}/engine/camera.cpp
        ${project_dir}/engine/states/shift.cpp
        ${project_dir}/engine/states/idle.cpp
        ${project_dir}/engine/states/turn.cpp
        $<TARGET_OBJECTS:configuration>
        $<TARGET_OBJECTS:logger>
        $<TARGET_OBJECTS:vulkan_tools>
        $<TARGET_OBJECTS:glfw_tools>
        )

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)

include_directories(${project_dir})

include(${project_dir}/tools/CMakeLists.txt)
include(${project_dir}/shaders/CMakeLists.txt)

target_include_directories(caravaner2 PUBLIC ${GLM_INCLUDE_DIR} ${Vulkan_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
if(WIN32)
    target_compile_definitions(caravaner2 PUBLIC -DVK_USE_PLATFORM_WIN32_KHR -DGLFW_EXPOSE_NATIVE_WIN32 -DGLFW_EXPOSE_NATIVE_WGL)
elseif(UNIX)
    target_compile_definitions(caravaner2 PUBLIC -DVK_USE_PLATFORM_XCB_KHR)
    include_directories("${project_dir}/tools/glfw-3.3.2/include")
endif()

target_compile_definitions(caravaner2 PUBLIC -DGLFW_INCLUDE_VULKAN)

target_link_libraries(caravaner2 glfw glm ${Vulkan_LIBRARY})

add_compile_definitions(VULKAN_DEBUG)