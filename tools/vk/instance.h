//
// Created by Владимир on 26.08.2020.
//


#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "tools/exceptions.h"
#include "tools/vk/surface.h"
#include "tools/vk/validationLayers.h"

#ifndef TOOLS_VK_INSTANCE_H
#define TOOLS_VK_INSTANCE_H
namespace vk
{
	class Instance
	{
		public:
			/// Конструктор
			/// \param window Окно вывода
			explicit Instance ( GLFWwindow *window );

			/// Деструктор
			~Instance ();

			/// Получить указатель на экземпляр Vulkan
			/// \return Указатель
			VkInstance
			getInstance () const;

			Surface *
			getSurface () const;

		private:
			/// Экземпляр Vulkan
			VkInstance instance;

			#ifdef VULKAN_DEBUG

			/// Слои проверки
			ValidationLayers *validationLayers;

			#endif
			/// Поверхность отрисовки
			Surface *surface;
	};
}// namespace vk
#endif//TOOLS_VK_INSTANCE_H
