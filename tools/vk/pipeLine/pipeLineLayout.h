//
// Created by Владимир on 08.09.2020.
//

#ifndef TOOLS_VK_PIPELINE_PIPELINELAYOUT_H
#define TOOLS_VK_PIPELINE_PIPELINELAYOUT_H

#include <vulkan/vulkan.h>
#include <tools/vk/pipeLine/descriptorSetLayout.h>

namespace vk
{
    class LogicalDevice;
    namespace pipeline
    {
        /// Макет конвеера
        class PipeLineLayout
            {
            public:
                /// Конструктор логическок устройство
                /// \param logicalDevice указатель
                PipeLineLayout ( LogicalDevice * logicalDevice );

                virtual ~PipeLineLayout ();

                /// Получить макет
                /// \return макет
                const VkPipelineLayout &
                getLayout () const;

                const DescriptorSetLayout &
                getDescriptorSetLayout () const;

            private:
                LogicalDevice * logicalDevice;
                pipeline::DescriptorSetLayout descriptorSetLayout;
                /// Макет конвеера
                VkPipelineLayout layout;
            };
    }
}
#endif //TOOLS_VK_PIPELINE_PIPELINELAYOUT_H
