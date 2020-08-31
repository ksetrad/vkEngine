set(vulkan_tools_src
        ${project_dir}/tools/vk/core.cpp
        ${project_dir}/tools/vk/instance.cpp
        ${project_dir}/tools/vk/logicalDevice.cpp
        ${project_dir}/tools/vk/physicalDevice.cpp
        ${project_dir}/tools/vk/surface.cpp
        ${project_dir}/tools/vk/validationLayers.cpp
        )

add_library(vulkan_tools
        OBJECT
        ${vulkan_tools_src})