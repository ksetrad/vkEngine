//
// Created by Владимир on 06.09.2020.
//

#ifndef TOOLS_VK_RENDERPASS_H
#define TOOLS_VK_RENDERPASS_H

#include <map>
#include <vector>
#include <vulkan/vulkan.h>
namespace vk
{
    class LogicalDevice;
    class SwapChain;

    class RenderPass
        {
        public:
            RenderPass (
                    vk::LogicalDevice * device ,
                    vk::SwapChain * swapChain
                       );

            virtual ~RenderPass ();

            virtual
            void
            install () = 0;

            const VkRenderPass &
            getRenderPass () const;

        protected:
            VkRenderPass renderPass;

            LogicalDevice * device;

            SwapChain * swapChain;
        };
}
#endif //TOOLS_VK_RENDERPASS_H
