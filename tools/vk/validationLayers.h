//
// Created by Владимир on 15.08.2020.
//

#ifndef TOOLS_VULKAN_VALIDATIONLAYERS_H
#define TOOLS_VULKAN_VALIDATIONLAYERS_H

#include <vector>
#include <vulkan/vulkan.h>

namespace vk
{
    /// Слои проверки работы Vulkan
    class ValidationLayers
        {
        public:

            /// Конструктор
            /// \param validationLayers массив слоев проверки
            explicit
            ValidationLayers ( const std::vector < std::string > & validationLayers );

            virtual ~ValidationLayers ();

            /// Получить слои проверки
            [[nodiscard]] const std::vector < const char * > &
            getValidationLayers () const;

            /// Параметры отладочных сообщений
            static VkDebugUtilsMessengerCreateInfoEXT
            constructDebugInfo ();

            /// Инициализация уровней проверки
            /// \param instance Vulkan
            /// \return результат инициализации
            VkResult
            initialize ( VkInstance * instance );

        private:
            /// Проверить наличие запрошенных слоев
            /// \return Результат доступности слоев
            bool
            checkLayers ();

            /// массив слоев проверки
            std::vector < const char * > validationLayers;

            /// Объект формирования отладочных сообщений
            VkDebugUtilsMessengerEXT debugMessenger;

            /// Указатель на Vulkan
            VkInstance * instance;

            /// Функция вывода отладочных сообщений
            static VKAPI_ATTR VkBool32 VKAPI_CALL
            debugCallback (
                    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity ,
                    VkDebugUtilsMessageTypeFlagsEXT messageType ,
                    const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData ,
                    void * pUserData
                          );
        };
}
#endif //TOOLS_VULKAN_VALIDATIONLAYERS_H
