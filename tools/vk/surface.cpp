//
// Created by Владимир on 31.08.2020.
//

#include "tools/vk/instance.h"
#include "tools/vk/surface.h"

using namespace vk;

Surface::Surface (
        Instance * instance ,
        GLFWwindow * window
                 )
        : instance ( instance )
{
        /// Создаем поверхность отрисовки
        if ( glfwCreateWindowSurface ( instance->getInstance () , window , nullptr , & surface ) != VK_SUCCESS )
        {
                throw vulkan_exception ( "failed to create window surface!" );
        }
}

Surface::~Surface ()
{
        vkDestroySurfaceKHR ( instance->getInstance () , surface , nullptr );
}

bool
Surface::checkPresent (
        const VkPhysicalDevice & physicalDevice ,
        const int & queueId
                      )
{
        VkBool32 presentSupport;
        vkGetPhysicalDeviceSurfaceSupportKHR ( physicalDevice , queueId , surface , & presentSupport );
        return presentSupport;
}

