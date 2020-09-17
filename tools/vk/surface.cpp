//
// Created by Владимир on 31.08.2020.
//

#include "tools/vk/surface.h"
#include "tools/vk/instance.h"

using namespace vk;

Surface::Surface (
		Instance *instance,
		GLFWwindow *window
) :
		instance ( instance )
{
	/// Создаем поверхность отрисовки
	if ( glfwCreateWindowSurface ( instance->getInstance (), window, nullptr, &surface ) != VK_SUCCESS )
	{
		throw vulkan_exception ( "failed to create window surface!" );
	}
}

Surface::~Surface ()
{
	vkDestroySurfaceKHR ( instance->getInstance (), surface, nullptr );
}

bool
Surface::checkPresent (
		const VkPhysicalDevice &physicalDevice,
		const int &queueId
)
{
	VkBool32 presentSupport;
	vkGetPhysicalDeviceSurfaceSupportKHR ( physicalDevice, queueId, surface, &presentSupport );
	return presentSupport;
}

Surface::Details
Surface::getSwapChainDetails ( const VkPhysicalDevice &physicalDevice )
{
	Details details;

	/// Получить возможности отображения для поверхности
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR ( physicalDevice, surface, &details.capabilities );

	/// Определить число поддерживаемых форматов
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR ( physicalDevice, surface, &formatCount, nullptr );

	/// Построить массив форматов
	if ( formatCount != 0 )
	{
		details.formats.resize ( formatCount );
		vkGetPhysicalDeviceSurfaceFormatsKHR ( physicalDevice, surface, &formatCount, details.formats.data () );
	}

	/// Определить число режимов представления
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR ( physicalDevice, surface, &presentModeCount, nullptr );

	/// Построить массив режимов представления
	if ( presentModeCount != 0 )
	{
		details.presentModes.resize ( presentModeCount );
		vkGetPhysicalDeviceSurfacePresentModesKHR ( physicalDevice, surface, &presentModeCount,
		                                            details.presentModes.data () );
	}

	/// Вернуть результаты
	return details;
}

const VkSurfaceKHR &
Surface::getSurface () const
{
	return surface;
}
