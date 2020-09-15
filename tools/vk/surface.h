//
// Created by Владимир on 31.08.2020.
//

#ifndef TOOLS_VK_SURFACE_H
#define TOOLS_VK_SURFACE_H

#include <vector>
#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>

namespace vk
{
	class Instance;
	/// Поверхность отображения
	class Surface
	{
		public:
		/// Параметры поверхности отрисовки
		struct Details {
			/// Параметры поверхности отрисовки
			VkSurfaceCapabilitiesKHR capabilities;
			/// Поддерживаемые поверхностиью форматы пикселя и
			/// связанные с ними цветовые пространства (это позволяет иметь всегда одинаковое значение цвета
			/// на разных мониторах
			std::vector< VkSurfaceFormatKHR > formats;
			/// Поддерживаемые воперхностью режимы презентации изображения
			std::vector< VkPresentModeKHR > presentModes;

			/// Проверить что форматы и режимы представления присутствуют в данной структуре параметров
			/// \return Результат проверки
			[[nodiscard]] bool
			isComplete () const
			{
				return !formats.empty () && !presentModes.empty ();
			}
		};

		/// Конструктор
		/// \param instance Экземпляр Vulkan
		/// \param window Окно вывода
		Surface ( Instance *instance, GLFWwindow *window );

		/// Деструктор
		virtual ~Surface ();

		/// Проверить подходит ли очередь физического устройства для отправки команд отображения на данной поверхности
		/// \param physicalDevice Физическое устройство
		/// \param queueId идентификатор очереди
		/// \return Результат проверки
		bool
		checkPresent (
		        const VkPhysicalDevice &physicalDevice,
		        const int &queueId );

		/// Проверить поддержку цепочки смены кадров
		/// \param physicalDevice Физичесий интерфейс
		/// \return Результат проверки
		Details
		getSwapChainDetails ( const VkPhysicalDevice &physicalDevice );

		/// Получить текущий дескриптор поверхности
		/// \return Дескриптор
		[[nodiscard]] const VkSurfaceKHR &
		getSurface () const;

		private:
		/// Экземпляр Vulkan
		Instance *instance;

		/// Поверхность отображения
		VkSurfaceKHR surface;
	};
}// namespace vk
#endif//TOOLS_VK_SURFACE_H
