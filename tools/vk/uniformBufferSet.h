//
// Created by Владимир on 11.09.2020.
//

#ifndef TOOLS_VK_UNIFORMBUFFERSET_H
#define TOOLS_VK_UNIFORMBUFFERSET_H

#include <vulkan/vulkan.h>
#include "core.h"

namespace vk
{
    /// Буффер глобальных объектов
    class UniformBufferSet
        {
        public:
            /// Буффер глобальных объектов
            /// \param core ядро Vulkan
            /// \param size размер буфера
            UniformBufferSet (
                    Core * core ,
                    const size_t & size
                             );

            ~UniformBufferSet ();

            const std::vector < VkBuffer > &
            getBuffers () const;

            void
            write (
                    const int & id ,
                    void * data ,
                    int size
                  );
        private:
            /// Логический интерфейс GPU
            LogicalDevice * device;

            /// Массив объектов буффера
            std::vector < VkBuffer > buffers;

            /// Массивы буфферной памяти
            std::vector < VkDeviceMemory > buffersMemmory;

        };
}
#endif //TOOLS_VK_UNIFORMBUFFERSET_H
